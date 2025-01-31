[Original BusyBox Readme](../README)
## About this fork

This fork is used within my forked [android-backup-project ](https://github.com/evermind-zz/android_backup_project).
It features a modified chown which can read from a script file full of chown commands:

```
read a script file with calls to chown via -F [filename] or -

basically this patch is dedicated to read a script
file with loads of calls to chown eg. like:

chown 0:0 /path/to/file
chown 0:0 /path/to/anotherFile
...

If chown would be called from within the script that would spawn
a new process everytime and consumes a lot of time. Hence we read
read such a script file as regular file or from stdin and feed it
internally.
```

It's based on BusyBox version 1.36.1
