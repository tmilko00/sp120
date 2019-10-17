
/*Napisati program koji prvo proèita koliko redaka ima datoteka,
tj. koliko ima studenata zapisanih u datoteci. Nakon toga potrebno
je dinamièki alocirati prostor za niz struktura studenata (ime, prezime, bodovi)
i uèitati iz datoteke sve zapise. Na ekran ispisati ime, prezime,apsolutni i relativni broj bodova.
Napomena:Svaki redak datoteke sadrži ime i prezime studenta, te broj bodovana kolokviju.relatvan_br_bodova = br_bodova/max_br_bodova*100

*/

#define _CRT_SECURE_NO_WARNINGS 
#define NAME_MAX (100)
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char ime[NAME_MAX];
	char prezime[NAME_MAX];
	int bodovi;
}_student;

int countLinesInFile(char fileName[]);
int loadStudentData(_student* student, int numberOfStudents,char fileName[]);
int findMaxPoints(_student* student, int numberOfStudents);
float calculateRelativePoints(_student* student, int maxPoints);

int main(int argc, char* argv[]) {
	   
	char fileName[20] = "studenti.txt";
	int lineCount = 0;
	int maxBodovi = 0;
	int i = 0;
	_student* student = NULL;
	lineCount= countLinesInFile(fileName);
	if (lineCount > 0) {
		printf("U fileu se nalazi %d studenata.\n", lineCount);
		student = (_student*)malloc((sizeof(_student) * lineCount));

		if (loadStudentData(student, lineCount, fileName) >= 0) {
			maxBodovi = findMaxPoints(student, lineCount);
			if (maxBodovi > 0) {
				for (i = 0;i < lineCount;i++) {
					if (student != NULL) {
						printf("%s %s %d %.2f\n", student[i].ime, student[i].prezime, student[i].bodovi, calculateRelativePoints(&student[i], maxBodovi));
					}
				}
			}
			else {
				printf("Svi imaju 0 bodova");
			}
		}
	}
	else printf("Nema studenata");

	if(student!=NULL)free(student);
	
	return 0;
}

int countLinesInFile(char fileName[]) {
	FILE* fp = NULL;
	int lineCount = 0;
	int znak = 0;
	fp = fopen(fileName, "r");
	if (fp!=NULL) {
		while ((znak = getc(fp)) != EOF) {
			if (znak == '\n')
				lineCount++;
		}
		lineCount++; //dodaj zadnju liniju
		fclose(fp);
		return lineCount;
	}
	printf("cant open file");
	return -1;
}
int loadStudentData(_student* student, int numberOfStudents,char fileName[])
{
	FILE* fp=NULL;
	int i = 0;
	int ret = 0;
	fp = fopen(fileName, "r");
	if (fp != NULL) {
		for (i = 0;i < numberOfStudents;i++) {
			
			ret=fscanf(fp, "%d %s %s", &student[i].bodovi, student[i].ime, student[i].prezime);
			if (ret != 3) {
				printf("krivo formatirani podatci");
				fclose(fp);
				return -1;
			}
		}
		fclose(fp);
		return 0;
	}

	printf("couldnt open file");
	return -1;
}

int findMaxPoints(_student* student, int numberOfStudents)
{
	int i = 0;
	int maxBodova = 0;
	if (student != NULL) {
		for (i = 0;i < numberOfStudents;i++) {
			if (student[i].bodovi > maxBodova)
				maxBodova = student[i].bodovi;
			
		}
		return maxBodova;
	}
	return -1;
}

float calculateRelativePoints(_student* student, int maxPoints)
{	
	float relativePoints = 0;
	relativePoints = (float)student->bodovi / (float)maxPoints * 100;
	return relativePoints;
}
