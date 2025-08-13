#!/bin/bash
# finder.sh

# 1) Kiểm tra tham số
if [ $# -ne 2 ]; then
    echo "Error: Two arguments required: filesdir searchstr"
    exit 1
fi

filesdir="$1"
searchstr="$2"

# 2) Kiểm tra thư mục tồn tại
if [ ! -d "$filesdir" ]; then
    echo "Error: $filesdir is not a directory"
    exit 1
fi

# 3) Tính X = số file (đệ quy)
# 2>/dev/null để tránh thông báo Permission denied làm bẩn output
X=$(find "$filesdir" -type f 2>/dev/null | wc -l)

# 4) Tính Y = số dòng khớp searchstr
# -R: đệ quy, -F: tìm chuỗi cố định (không coi là regex)
# --binary-files=without-match: bỏ qua file nhị phân để không đếm sai
Y=$(grep -R -F --binary-files=without-match "$searchstr" "$filesdir" 2>/dev/null | wc -l)

# 5) In đúng định dạng yêu cầu
echo "The number of files are $X and the number of matching lines are $Y"
