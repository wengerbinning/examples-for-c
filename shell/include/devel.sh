
devel_error() {
	echo -ne "\e[31m"
	echo -ne $@
	echo -ne "\e[0m"
	echo -ne '\n'
}


devel_warning() {
	echo -ne "\e[33m"
	echo -ne $@
	echo -ne "\e[0m"
	echo -ne '\n'
}



devel_notice() {
	echo -ne "\e[34m"
	echo -ne $@
	echo -ne "\e[0m"
	echo -ne '\n'
}



devel_info() {
	echo -ne "\e[32m"
	echo -ne $@
	echo -ne "\e[0m"
	echo -ne '\n'
}
