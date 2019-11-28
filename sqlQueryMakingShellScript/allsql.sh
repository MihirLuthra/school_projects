#The user is first asked to enter a file where he wants to enter all the code
#the code is written in the order in which user enters it
#no check is performed on the code
#user's choice is inputted in cnt
#e.g., cnt=1
#then the user is asked to enter a name
#to the program simply appends the line CREATE DATABASE $name; to the file that user gave

echo "\nif you input to create a thing that already exists it will get replaced!\n"
echo "Enter a file name where you want to save all your content:"
read fl
while [ 0 ]
do
echo "What do you want to do:"
echo "1.create a database"
echo "2.create a table"
echo "3.add fields to a table"
echo "4.delete records from a table"
echo "5.use a database"
echo "6.drop a database"
echo "7.Add records into table"
echo "8.Drop a table"
echo "9.Describe a table"
echo "10.Display contents of a table/tables"
echo "11.Modify field of a table"
echo "12.Modify record of a table"
echo "13.Insert into table by column name"
echo "14.Exit"
read cnt

if [ $cnt = 1 ]
then
    echo "Enter name of the database:"
    read dat
    echo "DROP DATABASE $dat;" >> $fl
    echo "CREATE DATABASE $dat;" >> $fl
elif [ $cnt = 2 ]
then
    echo "Enter name of the table:"
    read tbl
    echo "DROP TABLE $tbl;" >> $fl
    echo "Do you want to enter fields to it:(1=yes/0=no)"
    read no
    if [ $no = 0 ]
    then
        echo "CREATE TABLE $tbl;" >> $fl
    else
        echo "CREATE TABLE $tbl ( \c " >> $fl
        while [ 0 ]
        do
        echo "Enter name of the field:"
        read nm
        echo "Enter type:"
        read typ
        echo "$nm $typ \c" >> $fl
        echo "Do you want to enter more fields:(1=yes/0=no)"
        read yes
        if [ $yes = 1 ]
        then
            echo ",\c" >> $fl
            continue
        else
            echo ");" >> $fl
            break
        fi
        done
    fi
elif [ $cnt = 3 ]
then
    echo "Enter name of the table to which you want to fields:"
    read tab
    while [ 0 ]
    do
    echo "Enter field name:"
    read a
    echo "Enter type:"
    read b
    echo "ALTER TABLE $tab ADD ($a $b);" >> $fl
    echo "Do you want to enter more fields?(1=yes/0=no)"
    read yes
        if [ $yes = 1 ]
        then
            continue
        else
            break
        fi
    done
elif [ $cnt = 4 ]
then
    echo "Enter name of the table from which you want to delete the records:"
    read tb
    while [ 0 ]
    do
    echo "Enter condition:"
    read a
    if [ -n "$a" ]
    then
        echo "DELETE FROM $tb WHERE $a ;" >> $fl
    else
        echo "DELETE FROM $tb ;" >> $fl
    fi
    echo "Do you want to delete more records?(1=yes/0=no)"
    read y
        if [ $y = 1 ]
        then
            continue
        else
            break
        fi
    done
elif [ $cnt = 5 ]
then
    echo "Enter name of the database:"
    read d
    echo "USE $d;" >> $fl
elif [ $cnt = 6 ]
then
    echo "Enter name of the database:"
    read dta
    echo "DROP DATABASE $dta;" >> $fl
elif [ $cnt = 7 ]
then
    echo "Enter name of the table to which you want to add the records:"
    read tl
    echo "Enter column list( optional ) :"
    read ab
    if [ -n "$ab" ]
    then
        echo "INSERT INTO $tl ( $ab ) VALUES  \c" >> $fl
    else
        echo "INSERT INTO $tl VALUES \c" >> $fl
    fi
    while [ 0 ]
    do
    echo "Enter values( seperate by commas ):"
    read ba
    echo " ( $ba ) \c" >> $fl
    echo "Do you want to add more records?(1=yes/0=no)"
    read ys
        if [ $ys = 1 ]
        then
        echo ",\c" >> $fl
            continue
        else
            echo ";" >> $fl
            break
        fi
    done
elif [ $cnt = 8 ]
then
    echo "Enter name of the table:"
    read tble
    echo "DROP $tble;" >> $fl
elif [ $cnt = 9 ]
then
    echo "Enter a table name:"
    read q
    echo "DESC $q;" >> $fl
elif [ $cnt = 10 ]
then
    echo "Enter table name/names( seperate by commas ) from which you want to fetch data:"
    read p
    echo "Enter data:"
    read da
    echo "SELECT $da FROM $p \c" >> $fl
    echo "Enter condition:( optional )"
    read cnd
        if [ -n "$cnd" ]
        then
            echo "WHERE $cnd \c" >> $fl
        fi
    echo "Enter the way you want to group it:( optional )"
    read way
        if [ -n "$way" ]
        then
            echo "GROUP BY $way \c" >> $fl
            echo "( optional )Enter condition for grouping:"
            read gcnd
            if [  -n "$gcnd" ]
            then
                echo "HAVING $gcnd \c" >> $fl
            fi
        fi
    echo "(optional)Enter a column name to which you want to apply order by followed by ASC or DESC:"
    read col
    if [ -n "$col" ]
    then
        echo "ORDER BY $col \c" >> $fl
    fi
    echo ";" >> $fl
elif [ $cnt = 11 ]
then
    echo "Enter table name:"
    read tbla
    echo "Enter name of the record that you want to modify:"
    read nam
    echo "Enter its new type:"
    read type
    echo "ALTER TABLE $tbla MODIFY( $nam $type );" >> $fl
elif [ $cnt = 12 ]
then
    echo "Enter table name:"
    read tabb
    echo "Assign the new values to the records( if records > 1 , seperate by commas )"
    read rec
    echo "UPDATE $tabb SET $rec \c" >> $fl
    echo "( optional )Enter condition:"
    read cnda
    if [ -n "$cnda" ]
    then
        echo "WHERE $cnda \c" >> $fl
    fi
    echo ";" >> $fl
elif [ $cnt = 13 ]
then
    inc=0
    acount=0
    bcount=0
    echo "Enter table name:"
    read tdata
    while [ 0 ]
    do
    echo "Enter column name:"
    read value
    echo "INSERT INTO $tdata ( $value ) VALUES \c" >> $fl
    echo "Is the value a string?(1=yes/0=no)"
    read answer
        if [ $inc = 0 ]
        then
            while [ 0 ]
            do
            acount=`expr $acount + 1`
            echo "Enter values:"
            read newval
            if [ $answer = 0 ]
            then
                echo "( $newval ) \c" >> $fl
            else
                echo "( '$newval' ) \c" >> $fl
            fi
            echo "Do you want to add more records?(1=yes/0=no)"
            read ays
            if [ $ays = 1 ]
            then
                echo ", \c" >> $fl
                continue
            else
                echo ";" >> $fl
                inc=1
                break
            fi
            done
        else
            while [ 0 ]
            do
            bcount=`expr $bcount + 1`
            echo "Enter values:"
            read newval
            if [ $answer = 0 ]
            then
            echo "( $newval ) \c" >> $fl
            else
            echo "( '$newval' ) \c" >> $fl
            fi
            if [  $bcount -le `expr $acount - 1`  ]
            then
                echo ", \c" >> $fl
                echo "next record:"
                continue
            else
                echo ";" >> $fl
                break
            fi
            done
        fi
        echo "Do you want to add more cols?(1=yes/0=no)"
        read none
        if [ $none = 1 ]
        then
            continue
        else
            break
        fi
    done
elif [ $cnt = 14 ]
then
    break
fi
done