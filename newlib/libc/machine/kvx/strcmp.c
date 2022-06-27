#include <stdint.h>

typedef uint64_t uint64x2_t __attribute__((vector_size(2 * sizeof(uint64_t))));

#define cnt_trailzero(a) __builtin_kvx_bitcntd(a, ".tz")

#define DETECTNULL(X) \
    (((X) - 0x0101010101010101) & ~((X) | 0x7f7f7f7f7f7f7f7f))

/* Nonzero if X is not aligned on a "type" boundary */
#define UNALIGNED(type, X) ((uintptr_t)X & (sizeof (type) - 1))
/* Nonzero if either X or Y is not aligned on a "type" boundary */
#define UNALIGNED2(type, X, Y) (UNALIGNED(type, X) | UNALIGNED(type, Y))


/* Smallest page size */
#define PAGE_SIZE (4096)
/* Zero if X will cross pages on load of "type" */
#define PAGE_CROSS_SAFE(type, X) \
    (((uintptr_t)X & (PAGE_SIZE - sizeof(type))) ^ (PAGE_SIZE - sizeof(type)))
/* Zero if either X or Y will cross pages on load of "type" */
#define PAGE_CROSS_SAFE2(type, X, Y) \
    (PAGE_CROSS_SAFE(type, X) | PAGE_CROSS_SAFE(type, Y))


int
strcmp(const char *s1, const char *s2) {
    uint64_t has_null0;
    uint64_t has_null1;

    uint64x2_t *a1;
    uint64x2_t *a2;

    uint64x2_t vv1;
    uint64x2_t vv2;

    /* Compare strings 128 bits at a time until detecting a difference
        or a null terminator */
    a1 = (uint64x2_t *)s1;
    a2 = (uint64x2_t *)s2;
    do {
        /* Check for page crossing when doing unaligned loads */
        if (!PAGE_CROSS_SAFE2(uint64x2_t, a1, a2)) {
            char *s1_tmp = (char *)a1;
            char *s2_tmp = (char *)a2;

            /* Compare 1 byte at a time until the page has been crossed */
            do {
                unsigned char c1 = *s1_tmp++;
                unsigned char c2 = *s2_tmp++;
                if (c1 == '\0' || c1 != c2) {
                    return c1 - c2;
                }
            } while (!PAGE_CROSS_SAFE2(uint64x2_t, s1_tmp, s2_tmp));

            /* Update pointers */
            a1 = (uint64x2_t *)s1_tmp;
            a2 = (uint64x2_t *)s2_tmp;
        }

        vv1 = *a1++;
        vv2 = *a2++;
        has_null0 = DETECTNULL(vv1[0]);
        has_null1 = DETECTNULL(vv1[1]);
    } while ((vv1[0] == vv2[0] && vv1[1] == vv2[1]) &&
            !(has_null0 || has_null1));

    /* The strings are equal after iteration, return zero */
    if (vv1[0] == vv2[0] && vv1[1] == vv2[1] && (has_null0 || has_null1)) {
        return 0;
    }

    /* Edge case: The null terminator is stored in the last byte of
       the first 64 bits */
    if (vv1[0] == vv2[0] && has_null0) {
        return 0;
    }

    /* Otherwise count the trailing zeroes to determine where the
       first different bit is */
    uint64_t trail = cnt_trailzero((vv1[0] ^ vv2[0]) | has_null0);
    uint64_t v1 = vv1[0];
    uint64_t v2 = vv2[0];

    /* If the first 64 bits are equal, check the last 64 bits */
    if (vv1[0] == vv2[0]) {
        trail = cnt_trailzero((vv1[1] ^ vv2[1]) | has_null1);
        v1 = vv1[1];
        v2 = vv2[1];
    }

    /* Round to lower multiple of 8 to get the different byte */
    trail &= ~UINT64_C(7);

    const unsigned char c1 = v1 >> trail;
    const unsigned char c2 = v2 >> trail;

    return c1 - c2;
}
