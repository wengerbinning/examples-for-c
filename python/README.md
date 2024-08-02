
* 当前脚本不能与模块重名。




os.mkdir(path)
os.makedirs(path)
os.getcwd()
os.chdir(path)
os.path.exists(path)


time.strftime()
time.strftime()







argparse - 命令行选项、参数和子命令解析器。

parser = argparse.ArgumentParser()
partser.add_argument()

parser.parse_args()

* 不能添加参数-h, --help， 模块内部使用。



parser.add_argument(param, action, choices, const, default, dest, help, metavar, nargs, required, type, version)

action: 说明参数处理的方式
    [
        store, store_const, store_true, store_false,
        append, append_const,
        count,
        help,
        version
    ]

choices: 参数值的范围
const: 存储一个常量值

