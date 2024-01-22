
define devel_error
	@echo -ne '\e[31m'
	@echo -ne "develop - "
	@echo -ne $1
	@echo -ne '\e[0m'
	@echo -ne '\n'
endef

define devel_warning
	@echo -ne '\e[33m'
	@echo -ne "develop - "
	@echo -ne $1
	@echo -ne '\e[0m'
	@echo -ne '\n'
endef

define devel_notice
	@echo -ne '\e[34m'
	@echo -ne "develop - "
	@echo -ne $1
	@echo -ne '\e[0m'
	@echo -ne '\n'
endef

define devel_info
	@echo -ne '\e[32m'
	@echo -ne "develop - "
	@echo -ne $1
	@echo -ne '\e[0m'
	@echo -ne '\n'
endef
