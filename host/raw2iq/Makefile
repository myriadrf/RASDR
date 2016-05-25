# Utility makefile to quickly test builds on posix systems
all: build/raw2iq

build/raw2iq: src/CMakeLists.txt src/raw2iq.c
	@mkdir -p $(@D)
	@( cd $(@D) ; cmake ../src )
	@${MAKE} -C $(@D)

clean:
	@-rm -rf build
.PHONY : clean

run: build/raw2iq
	-@build/raw2iq --help
	@echo ""
	-build/raw2iq < /dev/null -o $$.csv
.PHONY : run

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... build (the default if no target is provided)"
	@echo "... clean"
	@echo "... run"
.PHONY : help
