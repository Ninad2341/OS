DATABASE = "student.txt"

function insert_data() {
if [ -e "DATABASE" ];
then
echo "Enter the record to insert : "
read record
echo "$record" >> "DATABASE"
echo "Record Added"

else
echo "Database does not exist"
fi 
}


function view_data() {
if [ -e "DATABASE" ];
then
echo "Database Contents : "
cat "DATABASE"
else
echo "Database does not exist"
fi
}


function delete_db() {
if [ -e "DATABASE" ];
then
rm "DATABASE"
echo "Database Deleted"
else
echo "Database does not exist"
fi
}


function create_db() {
if [ -e "DATABASE" ];
then
echo "File already exist"
else
touch "DATABASE"
echo "Database Created"
fi
}


function delete_record() {
if [ -e "DATABASE" ];
then
echo "Enter the record you want to Delete : "
read record
grep -vFx "$record" "DATABASE" > temp_db && mv temp_db "DATABASE"
echo "Record Deleted"
else
echo "Database does not exist"
fi
}


function modify_record() {
if [ -e "DATABASE" ];
then
echo "Enter the Record to Modify : "
read old_record
echo "Enter New Record to Replace : "
read new_record

sed -i "s|^$old_record$|$new_record|" "DATABASE"
echo "Record Modified"
else
echo "Database does not exist"
fi
}


while :
do
echo "-----------------------------"
echo "-----------------------------"
echo "Choose an Option"
echo "1. Create Database"
echo "2. Insert Record in Database"
echo "3. View Database"
echo "4. Delete Record"
echo "5. Modify Record"
echo "6. Delete Database"
echo "7. Exit"
read choice

case $choice in

1) create_db ;;
2) insert_data ;;
3) view_data ;;
4) delete_record ;;
5) modify_record ;;
6) delete_db ;;
7) exit ;;
*) echo "Invalid Choice"
esac
done


