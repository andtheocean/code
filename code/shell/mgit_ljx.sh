#cp -r /home/obsidian/program/ljx /home/obsidian/program/git
tar1name=$(date +%Y_%m_%d_%H_ljx.rar)
tar2name=$(date +%Y_%m_%d_%H_xp.rar)
cd ~/program/git
#rm *.tgz
find ../ljx -type f -not \( -path '*/matpower/*' -or -path '*/STM32F10x_FWLib/*'  -or -path '*FreeRTOS*' -or -path '*django*' -or -path '*B_GPS*'  -or -path '*book*' -or -path '*GPSControl' -or -path '*mongo*' \) \( -name "*.c" -or -name "*.h" -or -name "*.py" -or -name "*.nb" -or -name "*.m" -or -name "*.md" -or -name "*.xmind" \) |xargs rar a -r ~/program/git/$tar1name -hp928107lijiaxuan

rar a -r mark.rar ~/.config/google-chrome/Default/Bookmarks -hp928107lijiaxuan

cd /home/obsidian/virtualbox/xp/code
find ./ -type f -not \( -path '*STM32F10x_FWLib*' -or -path '*Driver*'  -or -path '*dist*' -or -path '*Library*' -or -path '*B_GPS*' -or -path '*include*' -or -path '*GPSControl' -or -path '*M4*' -or -path '*del*'  -or -name '*stm32f10x*'  \) \( -name "*.c" -or -name "*.h" -or -name "*.py" -or -name "*.nb" -or -name "*.v" -or -name "*.m" -or -name "*.png" -or -name "*.cpp" -or -name "*.md" -or -name "*.ui" -or -name "*.asm" -or -name "*.xmind" \) |xargs rar a -r ~/program/git/$tar2name -hp928107lijiaxuan
cd ~/program/git
git add .
git commit -a -m "store"
git push -u origin master
#cp ~/Downloads/*.pdf ~/program/ljx/book/ -f
