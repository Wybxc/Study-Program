#!/bin/bash

function buildtools(){
    gcc -g -c $1 -o $2 -stdc++
}

function buildprograms(){
    local outs=`echo $@| cut -d ' ' -f 3-`
    gcc -g $1 -o $2 $outs -stdc++
}

# 第一步：编译 tools 文件夹
tools_changed=0
for source in $(find 'tools/' -name '*.cpp'); do
    header=`echo $source | awk 'gsub(".cpp",".hpp"){print $0}'`
    output=`echo $source | awk 'gsub(".cpp",".out"){print $0}'`
    if [ $source -ot $output ]; then # 如果源代码在上一次编译之后没有更改
        if [ $header -ot $output ]; then # 如果头文件在上一次编译之后没有更改
            continue
        fi
    fi
    # 如果输出文件不存在，或者源代码或头文件有变动，重新编译
    buildtools $source $output
    echo Compile: $source -\> $output
    tools_changed=1
done

# 第二步：编译各个程序
folders = `ls -F | grep [0-9]`
for folder in $folders; do
    for source in $(find $folders -name '*.cpp'); do
        output=`echo $source | awk 'gsub(".cpp",".cpp.exe"){print $0}'`
        if [ $tools_changed -eq 0 ]; then
            if [ $source -ot $output ]; then # 如果源代码在上一次编译之后没有更改
                    continue
            fi
        fi
        # 如果输出文件不存在，或者源代码或头文件有变动，重新编译
        buildprograms $source $output `$(find 'tools/' -name '*.out'`)`
        echo Build: $source -\> $output
    done
done