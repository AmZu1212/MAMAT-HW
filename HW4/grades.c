#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grades.h"
#include "linked-list.h"
#define MALLOCERROR 1
#define SUCCESS 0
#define FAILURE 1
#define MAX_GRADE 100
#define MIN_GRADE 0
#define AVG_ERROR -1


struct grades {
	struct list* student_list;
};

struct student {
	int id;
	char* name;
	struct list* course_list;
};

struct course {
	int score;
	char* course_name;
};



/*gets a course and frees the memory from the heap*/
void course_destroy(void* element) {
	struct course* my_course = (struct course*)element;
	free(my_course->course_name);
	free(my_course);
}

/*clones course (grade and name)*/
int course_clone(void* element, void** output) {
	struct course* course_1 = (struct course*)element;
	struct course* course_2 = (struct course*)malloc(sizeof(struct course));
	if (course_2 == NULL) {
		return MALLOCERROR;
	}

	course_2->score = course_1->score;
	int length = strlen(course_1->course_name);
	course_2->course_name = (char*)malloc(sizeof(char) * (length + 1));
	if (course_2->course_name == NULL) {
		free(course_2);
		return MALLOCERROR;
	}
	strcpy(course_2->course_name, course_1->course_name);

	*output = course_2;
	return SUCCESS;
}

/*gets a student and frees the memory from the heap (name,courses)*/
void student_destroy(void* element){
	struct student* student_1 = (struct student*)element;
	list_destroy(student_1->course_list);
	free(student_1->name);
	free(student_1);
}

/*clones student (name, id, courses)*/
int student_clone(void* element, void** output) {
	struct student* student_1 = (struct student*)element;
	struct student* student_2 =
				(struct student*)malloc(sizeof(struct student));

	if (student_2 == NULL) {
		return MALLOCERROR;
	}
	

	int len = strlen(student_1->name);
	student_2->name = (char*)malloc(sizeof(char)* (len+1));

	if (student_2->name == NULL) {
		free(student_2);
		return MALLOCERROR;
	}

	strcpy(student_2->name, student_1->name);
	student_2->id = student_1->id;
	student_2->course_list = list_init(course_clone, course_destroy);

	if (student_2->course_list == NULL) {
		free(student_2->name);
		free(student_2);
		return FAILURE;
	}
	if((student_1->course_list)!=NULL){
		struct iterator* pnt = list_begin(student_1->course_list);
		if (pnt == NULL) {
			*output = student_2;
			return SUCCESS;
		}
	
		int length = list_size(student_1->course_list);
		for (int i = 0; i < length; i++) {
			if ((list_push_back(student_2->course_list, pnt) != 0)) {
				free(student_2->name);
				free(student_2);
				return FAILURE;
			}
			pnt = list_next(pnt);
		}
	}

	*output = student_2;
	return SUCCESS;
}

/*Initializes Grades*/
struct grades* grades_init() {
	struct grades* student_grades = 
	(struct grades*)malloc(sizeof(struct grades));
	if (student_grades == NULL) {
		return NULL;
	}
	student_grades->student_list = list_init(student_clone, student_destroy);
	if (student_grades->student_list == NULL) {
		free(student_grades);
		return NULL;
	}
	return student_grades;
}

/*gets a grade and frees the memory from heap*/
void grades_destroy(struct grades* grades) {
	list_destroy(grades->student_list);
	free(grades);
}

/*gets grades and looks for a student with the given id,
 returns an iterator to the student and NULL if there isn't one*/
struct iterator* id_exists(struct grades* grades ,int id){

	struct iterator* student_list = list_begin(grades->student_list);
	struct student* current;
	while(student_list != NULL){
		current = (struct student*)list_get(student_list);
		if(current == NULL)
		{
			return NULL;
		}
		if(current->id == id ){
			return student_list;
		}
		student_list =list_next(student_list);
	}
	return NULL;
}

/*adds a student to grades (name and id)*/
int grades_add_student(struct grades* grades, const char* name, int id) {
	
	if (grades == NULL) {
		return FAILURE;
	}
	
	struct iterator* pnt = list_begin(grades->student_list);
	if (pnt == NULL) {
		if (list_size(grades->student_list) != 0) {
			return FAILURE;
		}
	}

	if(pnt != NULL){
		pnt = id_exists(grades,id);
		if(pnt != NULL){
			return 1;
		}
	}
	
	struct student* new_student=(struct student*)
	malloc(sizeof(struct student));

	if (new_student == NULL) {
		return MALLOCERROR;
	}

	int length = strlen(name);
	new_student->id = id;
	new_student->name = (char*)malloc(sizeof(char) * (length + 1));
	new_student->course_list =NULL;

	if (new_student->name == NULL) {
		free(new_student);
		return MALLOCERROR;
	}

	strcpy(new_student->name, name);
	
	if (list_push_back(grades->student_list, new_student) != 0) {
		free(new_student->name);
		free(new_student);
		return FAILURE;
	}

	free(new_student->name);
	free(new_student);
	return SUCCESS;
}

/*adds a course to a student's(id) course list (course name and grade)*/
int grades_add_grade(struct grades* grades, const char* name,
 int id, int grade) {
	if (grades == NULL) {
		return FAILURE;
	}
	struct course* new_course = (struct course*)malloc(sizeof(struct course));
	if (new_course == NULL) {
		return MALLOCERROR;
	}
	int length = strlen(name);
	new_course->score = grade;
	new_course->course_name = (char*)malloc(sizeof(char) * (length + 1));
	if (new_course->course_name == NULL) {
		free(new_course);
		return MALLOCERROR;
	}
	strcpy(new_course->course_name, name);
	if (grade<MIN_GRADE || grade > MAX_GRADE) {
		free(new_course->course_name);
		free(new_course);
		return FAILURE;
	}
	struct iterator* pnt = list_begin(grades->student_list);
	while (pnt != NULL) {
		struct student* current_student = list_get(pnt);
		if ((current_student->id) == id) {
			struct iterator* current_course_list = list_begin(current_student->course_list);
			struct course* pnt_name = list_get(current_course_list);
			while (current_course_list!=NULL) {
				if (strcmp(pnt_name->course_name, name) == 0) {
					free(new_course->course_name);
					free(new_course);
					return FAILURE;
				}
				current_course_list = list_next(current_course_list);
				pnt_name = list_get(current_course_list);
			}
			if (list_push_back((current_student->course_list), new_course) != 0) {
				free(new_course->course_name);
				free(new_course);
				return FAILURE;
			}
			else {
				free(new_course->course_name);
				free(new_course);
				return SUCCESS;
			}
		}
		pnt = list_next(pnt);
	}
	free(new_course->course_name);
	free(new_course);
	return FAILURE;
}


/*calculates the grade average for a given student(id)*/
float grades_calc_avg(struct grades* grades, int id, char** out) {
	if (grades == NULL) {
		return AVG_ERROR;
	}
	float sum = 0;
	float avg = 0;
	struct iterator* pnt = list_begin(grades->student_list);
	if (pnt == NULL) {
		if (list_size(grades->student_list) != 0) {
			return AVG_ERROR;
		}
	}
	int length = 0;
	while (pnt != NULL) {
		struct student* current = list_get(pnt);
		if ((current->id) == id) {
			*out = (char*)malloc(sizeof(char) * (strlen(current->name) + 1));
			if (*out == NULL) {
				return AVG_ERROR;
			}
			strcpy(*out, current->name);
			struct list* course_list = current->course_list;
			length = list_size(course_list);
			if (length == 0) {
				return avg;
			}
			struct iterator* pnt_course = list_begin(course_list);
			if (pnt_course == NULL) {
				return AVG_ERROR;
			}
			while (pnt_course != NULL) {
				struct course* current_grade = list_get(pnt_course);
				if (current_grade == NULL) {
					return AVG_ERROR;
				}
				sum += current_grade->score;
				pnt_course=list_next(pnt_course);
			}
			avg = sum / length;
			return avg;
		}
		pnt = list_next(pnt);
	}
	*out = NULL;
	return AVG_ERROR;
}

/*prints the student's(id) name, courses and grades*/
int grades_print_student(struct grades* grades, int id) {
	if (grades == NULL) {
		return FAILURE;
	}
	struct iterator* pnt = list_begin(grades->student_list);
	if (pnt == NULL) {
		if (list_size(grades->student_list) != 0) {
			return FAILURE;
		}
	}
	while (pnt != NULL) {
		struct student* current_student = list_get(pnt);
		
		if ((current_student->id) == id) {
			struct iterator* pnt_course = 
							list_begin(current_student->course_list);
			printf("%s %d:", current_student->name, current_student->id);
			while (pnt_course != NULL) {
				struct course* current_course = list_get(pnt_course);
				if (current_course == NULL) {
					return FAILURE;
				}
				printf(" %s %d", current_course->course_name,
											 current_course->score);
				pnt_course = list_next(pnt_course);
				if(pnt_course!=NULL){
				printf(",");
				}
			}
			printf("\n");
			return SUCCESS;
		}
		pnt = list_next(pnt);
	}
	return FAILURE;
}

/*prints all of the students, with their courses and grades*/
int grades_print_all(struct grades* grades) {
	if (grades == NULL) {
		return FAILURE;
	}

	struct iterator* pnt = list_begin(grades->student_list);
	if (pnt == NULL) {
		return SUCCESS;
	}
	int length=list_size(grades->student_list);
	for(int i=0;i<length;i++){
		struct student* current_student = list_get(pnt);
		if (current_student == NULL) {
			return FAILURE;
		}
		if (grades_print_student(grades, current_student->id) != 0) {
			return FAILURE;
		}
		pnt=list_next(pnt);
	}
	return SUCCESS;
}
