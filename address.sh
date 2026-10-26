#! /bin/bash
cont=1
while [ $cont == 1 ]
do
echo "  1. Create File
    2. Insert Elements
    3. Display
    4. Search Record
    5. Modify Record
    6. Delete Record
    7. Delete File"

echo -e "Enter choice: "
read ch
case $ch in

1)
    echo -e "Enter the filename: "
    read Filename
    if [ -f $Filename ]
    then
        echo -e "\nFile Exists"
    else
        touch $Filename
        echo -e "\nFile is created"
        
    fi
    ;;  
 
2)
    echo -e "Enter the filename: "
    read Filename   
    echo -e "Enter number of students: "
    read n
    echo -e "Eid\tEname\tEcity\tEmobile">>$Filename
    for ((i=0;i<n;i++))




    do
        echo -e "\nEnter Eid: "
        read Eid
        
        echo "Enter Ename: "
        read Ename
        
        echo "Enter Ecity: "
        read Ecity
        
        echo "Enter Emobile: "
        read Emobile
        
        echo -e "\n$Eid\t$Ename\t$Ecity\t$Emobile">>$Filename
    done
    ;;
    
3)
    echo -e "Enter the filename: "
    read Filename
    cat $Filename
    ;;
    
4) 
    echo -e "Enter the filename: "
    read Filename
    
    echo "Enter value to search: "
    read search

    echo -e "\nSearch Result: "
    grep -i "$search" "$Filename"
    ;;          
    

5)
    echo -e "Enter the filename: "
    read Filename

    echo -e "Enter Eid of record to modify: "
    read Eid









    if grep -q "^$Eid   " "$Filename"
    then
        echo -e "\nEnter new Eid: "
        read newEid

        echo "Enter new Ename: "
        read newEname

        echo "Enter new Ecity: "
        read newEcity

        echo "Enter new Emobile: "
        read newEmobile

        while IFS= read -r line
            do
                    if echo "$line" | grep -q "^$Eid    "
                    then
                        echo -e "$newEid\t$newEname\t$newEcity\t$newEmobile" >> temp
                    else
                        echo "$line" >> temp
                 fi
            done < "$Filename"

            cat temp > "$Filename"
            rm temp

            echo "Record modified successfully."
     else
        echo "Record not found."
   
    fi
    ;;
    
6)
    echo -e "Enter the filename: "
    read Filename

    if [ -f "$Filename" ]
    then
        echo -e "Enter Eid of record to delete: "
        read Eid

        grep -v "^$Eid  " "$Filename" > temp
        cat temp > "$Filename"
        rm temp
        echo "Record deleted successfully."
    else
        echo -e "\nFile does not exist."
    fi
    ;;  

7)
    echo -e "Enter the filename: "
    read Filename
    if [ -f $Filename ]
    then
        rm $Filename
        echo -e "\nFile deleted."
    else
        echo -e "\nFile does not exist."
    fi
    ;;  
        
*)
    echo "Invalid choice"
 ;;
   
esac
echo -e "Do you want to continue (Enter 0 if terminate) "
read cont
done
