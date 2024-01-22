

Format

* ECS
* `[`
* formatCode
* `m`

```shell
\e[0m
```

#### ECS

* `\e`
* `\033`
* `\x1B`

### FormatCode

#### Formatting

| Code | Desc |
|:---- |:---- |
| 1 | Bold        |
| 2 | Dim         |
| 4 | Undeerlined |
| 5 | Blink       |
| 7 | invert      |
| 8 | Hidden      |

#### Reset

| Code | Desc |
|:---- |:---- |
| 0  | 重置所有属性  |
| 21 | Dim         |
| 22 | Undeerlined |
| 24 | Blink       |
| 25 | invert      |
| 27 | 重设        |
| 28 | 重设隐藏      |

##### 8/16 色


* 前景色： 39, 30-37, 90-97
* 背景色： 49, 40-47, 100-107

#### 88/256 色

```
\e[38;5;codem
\e[48;5;codem
```

* 1 - 256









```
echo $TERM
tput -T xterm-88color colors
```


ls /usr/share/terminfo/
find /usr/share/terminfo/ -type f -printf '%f '

xterm-256color



#### xterm

xterm is the standard terminal emulator for the X Window System.

* xterm-256color

#### screen

