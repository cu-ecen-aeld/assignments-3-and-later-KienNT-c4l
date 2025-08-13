#!/bin/bash

writefile=$1
writestr=$2

# 1. Kiểm tra đủ tham số
if [ -z "$writefile" ] || [ -z "$writestr" ]; then
    echo "Error: Missing arguments"
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

# 2. Tạo thư mục chứa file
mkdir -p "$(dirname "$writefile")" || {
    echo "Error: Could not create directory"
    exit 1
}

# 3. Ghi nội dung vào file (overwrite)
echo "$writestr" > "$writefile" || {
    echo "Error: Could not write to file"
    exit 1
}

exit 0
