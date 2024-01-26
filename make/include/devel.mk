
define devel/rule/error
	@echo -ne '\e[31m'
	@echo -ne "develop - "
	@echo -ne $1
	@echo -ne '\e[0m'
	@echo -ne '\n'
endef

define devel/rule/warning
	@echo -ne '\e[33m'
	@echo -ne "develop - "
	@echo -ne $1
	@echo -ne '\e[0m'
	@echo -ne '\n'
endef

define devel/rule/notice
	@echo -ne '\e[34m'
	@echo -ne "develop - "
	@echo -ne $1
	@echo -ne '\e[0m'
	@echo -ne '\n'
endef

define devel/rule/info
	@echo -ne '\e[32m'
	@echo -ne "develop - "
	@echo -ne $1
	@echo -ne '\e[0m'
	@echo -ne '\n'
endef

define devel/make/notice
	$(info $1)
endef

define devel/make/info
	$(info $1)
endef