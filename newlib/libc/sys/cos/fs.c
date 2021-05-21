char *getcwd(char *buf, size_t size)
{
        errno = -ENOENT;
        return NULL;
}
long pathconf(const char *path, int name)
{
        errno = -ENOENT;
        return -1;
}
