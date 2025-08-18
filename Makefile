# Linux C Lab - Root Makefile
# 모든 서브프로젝트를 관리하는 마스터 Makefile

# 서브프로젝트 디렉토리
SUBDIRS = logger my_string linked_list

# 기본 타겟
.PHONY: all clean test install help $(SUBDIRS)

all: $(SUBDIRS)

# 각 서브프로젝트 빌드
$(SUBDIRS):
	@echo "Building $@..."
	@$(MAKE) -C $@ all

# 테스트 실행
test:
	@echo "Running tests for all projects..."
	@for dir in $(SUBDIRS); do \
		if [ -f $$dir/Makefile ]; then \
			echo "Testing $$dir..."; \
			$(MAKE) -C $$dir test 2>/dev/null || echo "No test target in $$dir"; \
		fi; \
	done

# Google Test 실행 (logger만)
gtest:
	@echo "Running Google Test for logger..."
	@$(MAKE) -C logger gtest
	@$(MAKE) -C logger run_gtest

# 정리
clean:
	@echo "Cleaning all projects..."
	@for dir in $(SUBDIRS); do \
		if [ -f $$dir/Makefile ]; then \
			echo "Cleaning $$dir..."; \
			$(MAKE) -C $$dir clean; \
		fi; \
	done

# 설치 (라이브러리들)
install:
	@echo "Installing libraries..."
	@for dir in $(SUBDIRS); do \
		if [ -f $$dir/Makefile ]; then \
			echo "Installing $$dir..."; \
			$(MAKE) -C $$dir install 2>/dev/null || echo "No install target in $$dir"; \
		fi; \
	done

# 도움말
help:
	@echo "Linux C Lab - Available targets:"
	@echo ""
	@echo "  all        - Build all subprojects"
	@echo "  logger     - Build logger library only"
	@echo "  my_string  - Build my_string library only"
	@echo "  linked_list- Build linked_list project only"
	@echo "  test       - Run tests for all projects"
	@echo "  gtest      - Run Google Test for logger"
	@echo "  clean      - Clean all build artifacts"
	@echo "  install    - Install all libraries"
	@echo "  help       - Show this help message"
	@echo ""
	@echo "Individual project commands:"
	@echo "  make -C logger <target>     - Run specific target in logger"
	@echo "  make -C my_string <target>  - Run specific target in my_string"
	@echo "  make -C linked_list <target>- Run specific target in linked_list"