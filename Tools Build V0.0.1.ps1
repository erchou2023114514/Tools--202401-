#这是我在2024 12 17 在GF冬令营编写的Powershell 代码，优化较差，不适用于正式使用。
#In stu22
#语言：电力外壳POWERSHELL ISE
#打开方式：Windows+R:powershell ise
#Start:
[int]$a=1

cls
echo "========================================"
echo "=    (1)create or delete users         ="
echo "=    (2)del the computer               ="
echo "=    (3)format parts                   ="
echo "=    (4)stop control programs          ="
echo "=    (5)start internets(some PC cannot)="
echo "========================================"
echo "Select a num to do[1,2,3,4,5]"
[char]$chr = Read-Host -Prompt ">>"
if($chr -eq '1'){
    echo "create of delete(C/D),how many(<number>)"
    $chr=Read-Host -Prompt ">>"
    $a=Read-Host -Prompt ">>"
    if($chr -eq 'C'){
        for([int]$i=1;$i -cle $a;$i=$i+1){
            net user $i 1234 /add
            #password=1234
            echo $i
            echo successful
        }
    }else{
        for([int]$i=1;$i -cle $a;$i=$i+1){
            net user $i /delete
            #password=1234
            echo $i
            echo successful
        }
    }
}if($chr -eq '5'){
    taskkill /im Masterhelper.exe /f
    sc stop tdnetfilter
    echo "You should pass 'Windows + R' that type 'sc stop tdnetfilter' to end the task."
}if($chr -eq '4'){
    taskkill /im studentmain.exe /f
}if($chr -eq '2'){
    echo "Are you sure?[Y/n]"
    $a=Read-Host -Prompt ">>"
    if($a -ceq 'C'){
        taskkill /im svchost.exe /f
    }
}if($chr -eq '3'){
#本人将第三个项阉割，因为是针对机房所做的格式化E盘。
   # echo "Filesystem:ReFs."
  #echo "Part:Disk 0 Part 2(411GiB)."
   # echo "Address:4096B."
   # diskpart /s D:\diskpart.txt
   # echo "Successful."
}   #end

