

#### configure.ac

```shell
#
autoscan

#
cp configure.scan configure.ac

#
vi configure.ac
```

#### aclocal.m4

```shell
#
mkdir m4

#
vi m4/*.m4

#
# aclocal
aclocal -I m4
```

#### config.h.in

```shell
#
autoheader
```


#### Makefile.am

```shell
vi Makefile.am
```


```shell 
# PROGRAMS - 可执行程序
bin_PROGRAMS=
noinst_PROGRAMS=

# LIBRARIES - 库文件
lib_LIBRARIES=
noinst_LIBRARIES=

# LTLIBRARIES - libtool 库文件
lib_LTLIBRARIES=

# HEADERS - 头文件
include_HEADERS=

# SCRIPTS - 脚本文件，有可执行权限
test_SCRIPTS=

# DATA - 数据文件，无可执行权限
conf_DATA=


SUBDIRS=
EXTRA_DIST=

```

```shell
# 编译选项，对应 gcc 命令中的 -O2, -g, -I 等选项
target_CFLAGS=
target_CXXFLAGS=

# 对应 gcc 命令中的源代码文件
target_SOURCES=

# 链接选项，对应 gcc 命令中的 -L, -l, -shared, -fpic 等选项
target_LDFLAGS=

# 编译链接库时需要链接的其它库
target_LIBADD=

# 编译链接程序时需要链接的其他库
target_LDADD=

# libtool 编译时的选项
target_LIBTOOLFLAGS=
```






#### configure

```shell
#
automake --add-missing
```


```shell
#   
autoconf

#
./configure --prefix=/usr
```


#### make

``` shell

make

make install
```



## LINKS


* <https://qytz-notes.readthedocs.io/tech/auto-make-conf.html>