// ***
// *** Do NOT modify this file
// ***

#include "hw5.h"

int main(int argc, char **argv)
{
    /*printf("DEBUG: Program started with %d arguments\n", argc); 
    for (int i = 0; i < argc; i++) 
    { 
        printf(" argv[%d]: %s\n", i, argv[i]);
    }*/
    // argv[1]: input file name
    // argv[2]: output file name, sorted by ID
    // argv[3]: output file name, sorted by name
    if (argc < 4)
    {
        return EXIT_FAILURE;
    }

    Student *stu;
    int numelem;
    //printf("DEBUG: About to call StudentRead with file: %s\n", argv[1]);
    if (StudentRead(argv[1], &stu, &numelem) == false)
    {
        //printf("DEBUG: StudentRead failed\n");
        return EXIT_FAILURE;
    }
   // printf("DEBUG: StudentRead succeeded, read %d students\n", numelem);

    // You can use StudentPrint function to print the data from StudentRead
    // StudentPrint(stu, numelem);

    // sort students by ID
    sortStudents(stu, numelem, compareID);
    if (!areStudentsSorted(stu, numelem, compareID))
    {
        return EXIT_FAILURE;
    }
    if (StudentWrite(argv[2], stu, numelem) == false)
    {
        return EXIT_FAILURE;
    }

    // sort students by name
    sortStudents(stu, numelem, compareName);
    if (!areStudentsSorted(stu, numelem, compareName))
    {
        return EXIT_FAILURE;
    }
    if (StudentWrite(argv[3], stu, numelem) == false)
    {
        return EXIT_FAILURE;
    }

    free(stu);
    return EXIT_SUCCESS;
}
