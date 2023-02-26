# MixedObjectSerializing
classes:
a. Full name with the fields first name, last name, patronymic (patronymic optional).
b. Student with the fields full name, array of grades, average score.
c. Student group with the field array of students.

 Create a Student Group class that implements the interfaces:
class StudentGroup {
void open() = 0; // binary deserialization to file 
void save() = 0; // binary serialization to file
};
