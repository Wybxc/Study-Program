.RECIPEPREFIX = > 

CC := gcc -g
folders := $(shell ls -F | grep [0-9])
source := $(shell find $(folders) -name '*.cpp')
target := $(source:.cpp=.cpp.exe)

tools_source := $(shell find tools -name '*.cpp')
tools_header := $(shell find tools -name '*.hpp')
tools_target := $(tools_source:.cpp=.o)

.PHONY: all clean

all: $(target)

$(target): $(source) $(tools_target)
> $(CC) $(shell echo $@ | awk 'gsub(".cpp.exe",".cpp"){print $0}') -o $@ $(tools_target) -lstdc++

$(tools_target): $(tools_source) $(tools_header)
> $(CC) -c $(shell echo $@ | awk 'gsub(".o",".cpp"){print $0}') -o $@ -lstdc++

clean:
> rm -rf */*.exe