.RECIPEPREFIX = > 

CC := gcc -g -lstdc++

folders := $(shell ls -F | grep [0-9])
source := $(shell find $(folders) -name '*.cpp')
target := $(source: %.cpp = %.cpp.exe)

tools_source := $(shell find tools -name '*.cpp')
tools_header := $(shell find tools -name '*.hpp')
tools_target := $(tools_source: %.cpp = %.o)

all: $(target)

$(target): $(source) $(tools_target)
> $(CC) $< -o $@ $(tools_target)

$(tools_target): $(tools_source) $(tools_header)
> $(CC) -c $< -o $@ 