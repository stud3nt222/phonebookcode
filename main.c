#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50

// Структура для зберігання контактної інформації
typedef struct { 
	int num;
	char phoneNumber[N];
	char lastname[N];
	char groups[N];
	char groups2[N];
	char workplace[N];
	char email[N];
}Contact;
Contact* memory(int);
FILE* fp; // Вказівник на файл

// Службові функції
void infomemory(Contact* Contacts);
int openFile(const char[], const char[]);
int scanContact(Contact* Contacts, char pytfiles[], int luk);
void editContact(int coun, Contact* Contacts, char pytfiles[]);
int openFile(const char mode[], const char file[]);
int addContact(Contact* Contacts, int coun, char pytfiles[]);
int infoContact(Contact* Contacts, int coun);
int deleteContact(Contact* Contacts, int coun, char pytfiles[]);
void searchContact(Contact* Contacts, int coun);
void sortContact(Contact* Contacts, int coun);

// Функція виділення пам'яті для масиву контактів
Contact* memory(int luk) {
	Contact* massive = (Contact*)malloc(luk * sizeof(Contact));
	if (massive == NULL) {
		return NULL;
	}
	else {

		return massive;
	}
}

// Функція для перевірки виділення пам'яті
void infomemory(Contact* Contacts)
{
	if (Contacts == NULL) {
		printf("Ошибка динамічний масив не був створений!\n");
	}
	else {
		printf("Пам'ять для динамічного масива була розподілена!\n");
	}
}

// Функція для редагування контакту
void editContact(int coun, Contact* Contacts, char pytfiles[])
{
	if (coun == 0) {
		printf("Контактів нема\n");
	}
	else {
		printf("Введіть індекс контакту, який бажаєте редагувати: ");
		int m = -1, cd;
		int b;
		scanf_s("%d", &cd);
		for (int c = 0; c < coun; c++) {
			if (Contacts[c].num == cd) {
				m = c;
			}
		}
		if (m == -1) {
			printf("Некоректний індекс контакту.\n");
		}
		else {
			do {
				printf("\nОберіть поле для редагування:\n");
				printf("1. Номер телефону\n");
				printf("2. Прізвище\n");
				printf("3. Групу 1\n");
				printf("4. Групу 2\n");
				printf("5. Місце роботи\n");
				printf("6. Електронна адреса\n");
				printf("0. Завершити редагування\n");
				printf("Виберіть опцію: ");
				scanf_s("%d", &b);
				switch (b) {
				case 1:
					printf("\nВведіть номер телефону: ");
					scanf_s("%s", Contacts[m].phoneNumber, N);
					break;
				case 2:
					printf("Введіть прізвище: ");
					scanf_s("%s", Contacts[m].lastname, N);
					break;
				case 3:
					printf("Введіть назву групи 1 (Родичі, Співробітники, Друзі): ");
					scanf_s("%s", Contacts[m].groups, N);
					break;
				case 4:
					printf("Введіть назву групи 2 (Родичі, Співробітники, Друзі): ");
					scanf_s("%s", Contacts[m].groups2, N);
					break;
				case 5:
					printf("Введіть місце роботи: ");
					scanf_s("%s", Contacts[m].workplace, N);
					break;
				case 6:
					printf("Введіть електронну адресу: ");
					scanf_s("%s", Contacts[m].email, N);
					break;
				default:
					if (b != 0) {
						printf("Неправильний вибір номера меню\n");
					}
					break;
				}
			} while (b != 0);
			openFile("w+", pytfiles); // запис контактів у файл
			for (int n = 0; n < coun; n++) {
				fprintf(fp, "\n%d ", Contacts[n].num);
				fprintf(fp, "%s ", Contacts[n].phoneNumber);
				fprintf(fp, "%s ", Contacts[n].lastname);
				fprintf(fp, "%s ", Contacts[n].groups);
				fprintf(fp, "%s ", Contacts[n].groups2);
				fprintf(fp, "%s ", Contacts[n].workplace);
				fprintf(fp, "%s ", Contacts[n].email);
			}
			fclose(fp);
		}
	}
}

// Функція для відкриття файлу
int openFile(const char mode[], const char file[])
{
	fopen_s(&fp, file, mode);
	if (!fp)
	{
		puts("Не вдалося відкрити файл \n");
		return 0;
	}
	else
		return 1;

}

// Функція для зчитування контактів з файлу
int scanContact(Contact* Contacts, char pytfiles[], int luk) {
	openFile("r", pytfiles);
	int readcont = 0;
	for (int i = 0; i < luk; i++) {
		fscanf_s(fp, "%d", &Contacts[i].num);
		fscanf_s(fp, "%s", Contacts[i].phoneNumber, N);
		fscanf_s(fp, "%s", Contacts[i].lastname, N);

		fscanf_s(fp, "%s ", Contacts[i].groups, N);
		fscanf_s(fp, "%s ", Contacts[i].groups2, N);
		fscanf_s(fp, "%s ", Contacts[i].workplace, N);
		fscanf_s(fp, "%s ", Contacts[i].email, N);
		int x = Contacts[i].num;
		if (x > 0) {
			readcont++;
		}
	}
	fclose(fp);
	return readcont;
}

// Функція для додавання контакту
int addContact(Contact* Contacts, int coun, char pytfiles[]) {
	int cus = 0;
	char c[N];

	for (int l = 0; l < coun; l++) {
		if (Contacts[l].num > cus) {
			cus = Contacts[l].num;
		}
	}
	Contacts[coun].num = cus + 1;
	printf("\nВведіть номер телефону (обов'язково): ");
	scanf_s("%s", Contacts[coun].phoneNumber, N);
	printf("Введіть прізвище (обов'язково): ");
	scanf_s("%s", Contacts[coun].lastname, N);
	do {
		printf("Введіть групу 1 (Родичі, Співробітники, Друзі або 1 для пропуску): ");
		scanf_s("%s", c, N);
		if (strstr("-", c) != NULL) {
			puts("Введення '-' неможливе, оскільки це позначення пустого поля. Будь ласка, введіть інше значення:");
		}
	} while (strstr("-", c) != NULL);
	if (strstr("1", c) != NULL) {
		strcpy_s(Contacts[coun].groups, N, "-");
	}
	else
	{
		strcpy_s(Contacts[coun].groups, N, c);
	}
	do {
		printf("Введіть групу 2 (Родичі, Співробітники, Друзі або 1 для пропуску): ");
		scanf_s("%s", c, N);
		if (strstr("-", c) != NULL) {
			puts("Введення '-' неможливе, оскільки це позначення пустого поля. Будь ласка, введіть інше значення:");
		}
	} while (strstr("-", c) != NULL);
	if (strstr("1", c) != NULL) {
		strcpy_s(Contacts[coun].groups2, N, "-");
	}
	else
	{
		strcpy_s(Contacts[coun].groups2, N, c);
	}
	do {
		printf("Введіть місце роботи (або 1 для пропуску): ");
		scanf_s("%s", c, N);
		if (strstr("-", c) != NULL) {
			puts("Введення '-' неможливе, оскільки це позначення пустого поля. Будь ласка, введіть інше значення:");
		}
	} while (strstr("-", c) != NULL);
	if (strstr("1", c) != NULL) {
		strcpy_s(Contacts[coun].workplace, N, "-");
	}
	else
	{
		strcpy_s(Contacts[coun].workplace, N, c);
	}
	do {
		printf("Введіть Ел. Адресу (або 1 для пропуску): ");
		scanf_s("%s", c, N);
		if (strstr("-", c) != NULL) {
			puts("Введення '-' неможливе, оскільки це позначення пустого поля. Будь ласка, введіть інше значення:");
		}
	} while (strstr("-", c) != NULL);
	if (strstr("1", c) != NULL) {
		strcpy_s(Contacts[coun].email, N, "-");
	}
	else
	{
		strcpy_s(Contacts[coun].email, N, c);
	}
	openFile("at", pytfiles);
	fprintf(fp, "\n%d ", Contacts[coun].num); 
	fprintf(fp, "%s ", Contacts[coun].phoneNumber);
	fprintf(fp, "%s ", Contacts[coun].lastname);
	fprintf(fp, "%s ", Contacts[coun].groups);
	fprintf(fp, "%s ", Contacts[coun].groups2);
	fprintf(fp, "%s ", Contacts[coun].workplace);
	fprintf(fp, "%s ", Contacts[coun].email);
	fclose(fp);
}

// Функція для виведення інформації про контакти
int infoContact(Contact* Contacts, int coun) { 
	if (coun == 0) {
		printf("Контактів нема \n");
	}
	else {
		printf("\nІнформація про контакт:\n");
		printf("|№ контакту|  Номер телефону  |   Прізвище    |             Група             |    Місце роботи    |     Ел. Адреса \n");
		for (int i = 0; i < coun; i++) {
			printf("| №%5d   |%18s| %14s| %13s   %13s | %18s | %10s \n", Contacts[i].num, Contacts[i].phoneNumber, Contacts[i].lastname, Contacts[i].groups, Contacts[i].groups2, Contacts[i].workplace, Contacts[i].email);
		}
		fclose(fp);
	}
}

//Функція для видалення контактів
int deleteContact(Contact* Contacts, int coun, char pytfiles[]) {
	if (coun == 0) {
		printf("Контактів нема\n");
	}
	else {
		printf("Введіть індекс контакту, який бажаєте видалити: ");
		int v;
		int i = -1;
		scanf_s("%d", &v);
		for (int m = 0; m < coun; m++) {
			if (Contacts[m].num == v) {
				i = m;
			}
		}
		if (i == -1) {
			printf("Некоректний індекс контакту.\n");
		}
		else {
			for (i; i < coun; i++) {
				Contacts[i] = Contacts[i + 1];
			}
			coun--;
			openFile("w+", pytfiles);
			for (int n = 0; n < coun; n++) {
				fprintf(fp, "\n%d ", Contacts[n].num);
				fprintf(fp, "%s ", Contacts[n].phoneNumber);
				fprintf(fp, "%s ", Contacts[n].lastname);
				fprintf(fp, "%s ", Contacts[n].groups);
				fprintf(fp, "%s ", Contacts[n].groups2);
				fprintf(fp, "%s ", Contacts[n].workplace);
				fprintf(fp, "%s ", Contacts[n].email);
			}
			fclose(fp);
		}


	}
}

// Функція для пошуку контактів
void searchContact(Contact* Contacts, int coun) {
	if (coun == 0) {
		printf("Контактів немає\n");
	}
	else {
		printf("\n1) Номер телефона\n");
		printf("2) Прізвище\n");
		printf("3) Групи\n");
		printf("4) Місце роботи\n");
		printf("Для вихода із цього меню введіть 0\n");
		int r, h;
		int v;
		printf("Виберіть критерію для пошука: ");
		scanf_s("%d", &r);
		switch (r)
		{
		case 1:
			do {
				printf("Введіть номер телефону: ");
				char sur[N];
				scanf_s("%s", sur, N);

				int foundPhoneNumber = 0;
				printf("|№ контакту|  Номер телефону  |   Прізвище    |             Група             |    Місце роботи    |     Ел. Адреса \n");
				for (h = 0; h < coun; h++) {
					if (strstr(Contacts[h].phoneNumber, sur) != NULL) {
						printf("| №%5d   |%18s| %14s| %13s   %13s | %18s | %10s\n", Contacts[h].num, Contacts[h].phoneNumber, Contacts[h].lastname, Contacts[h].groups, Contacts[h].groups2, Contacts[h].workplace, Contacts[h].email);
						foundPhoneNumber = 1;
					}

				}
				if (foundPhoneNumber == 0) {
					printf("Контакт не знайдено\n");
				}

				printf("\nЧи бажаєте здійснити пошук знову? 1 - так 0 - ні\n");
				scanf_s("%d", &v);
			} while (v != 0);
			break;
		case 2:
			do {
				printf("Введіть прізвище: ");
				char sur2[N];
				scanf_s("%s", sur2, N);
				int foundSecondName = 0;
				printf("|№ контакту|  Номер телефону  |   Прізвище    |             Група             |    Місце роботи    |     Ел. Адреса \n");
				for (h = 0; h < coun; h++) {
					if (strstr(Contacts[h].lastname, sur2) != NULL) {
						printf("| №%5d   |%18s| %14s| %13s   %13s | %18s | %10s\n", Contacts[h].num, Contacts[h].phoneNumber, Contacts[h].lastname, Contacts[h].groups, Contacts[h].groups2, Contacts[h].workplace, Contacts[h].email);
						foundSecondName = 1;
					}
				}
				if (foundSecondName == 0) {
					printf("Прізвище контакта не знайдено\n");
				}

				printf("\nЧи бажаєте здійснити пошук знову? 1 - так 0 - ні\n");
				scanf_s("%d", &v);
			} while (v != 0);
			break;
		case 3:
			do {
				printf("Введіть групу (Родичі, Співробітники, Друзі): ");
				char sur3[N];
				scanf_s("%s", sur3, N);
				if (strstr("-", sur3) != NULL) {
					printf("Групу контактів не знайдено\n");
				}
				else {
					int foundGroup = 0;
					printf("|№ контакту|  Номер телефону  |   Прізвище    |             Група             |    Місце роботи    |     Ел. Адреса \n");
					for (h = 0; h < coun; h++) {
						if (strstr(Contacts[h].groups, sur3) != NULL || strstr(Contacts[h].groups2, sur3) != NULL) {
							printf("| №%5d   |%18s| %14s| %13s   %13s | %18s | %10s\n", Contacts[h].num, Contacts[h].phoneNumber, Contacts[h].lastname, Contacts[h].groups, Contacts[h].groups2, Contacts[h].workplace, Contacts[h].email);
							foundGroup = 1;
						}
					}
					if (foundGroup == 0) {
						printf("Групу контактів не знайдено\n");
					}
				}
				printf("\nЧи бажаєте здійснити пошук знову? 1 - так 0 - ні\n");
				scanf_s("%d", &v);
			} while (v != 0);
			break;
		case 4:
			do {
				printf("Введіть місце роботи: ");
				char sur4[N];
				scanf_s("%s", sur4, N);
				if (strstr("-", sur4) != NULL) {
					printf("Місце роботи контакта не знайдено\n");
				}
				else {
					int foundWorkPlace = 0;
					printf("|№ контакту|  Номер телефону  |   Прізвище    |             Група             |    Місце роботи    |     Ел. Адреса \n");
					for (h = 0; h < coun; h++) {
						if (strstr(Contacts[h].workplace, sur4) != NULL) {
							printf("| №%5d   |%18s| %14s| %13s   %13s | %18s | %10s\n", Contacts[h].num, Contacts[h].phoneNumber, Contacts[h].lastname, Contacts[h].groups, Contacts[h].groups2, Contacts[h].workplace, Contacts[h].email);
							foundWorkPlace = 1;

						}
					}
					if (foundWorkPlace == 0) {
						printf("Місце роботи контакта не знайдено\n");
					}
				}
				printf("\nЧи бажаєте здійснити пошук знову? 1 - так 0 - ні\n");
				scanf_s("%d", &v);
			} while (v != 0);
			break;
		default:
			printf("Неправильний вибір номера меню\n");
		}
	}
}

// Функція для сортування контактів за прізвищем
void sortContact(Contact* Contacts, int coun) { 
	char* parr;
	if (coun == 0) {
		printf("Контактів нема\n");
	}
	else {
		printf("\nІнформація про контакт:\n");
		printf("|№ контакту|  Номер телефону  |   Прізвище    |             Група             |    Місце роботи    |     Ел. Адреса \n");
		for (int q = 192; q <= 255; q++) {
			for (int s = 0; s < coun; s++) {
				parr = Contacts[s].lastname;
				if ((char)q == parr[0]) {
					printf("| №%5d   |%18s| %14s| %13s   %13s | %18s | %10s\n", Contacts[s].num, Contacts[s].phoneNumber, Contacts[s].lastname, Contacts[s].groups, Contacts[s].groups2, Contacts[s].workplace, Contacts[s].email);
				}
			}
		}
	}
}

// Головна функція програми
int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char pytfiles[N];
	int luk;
	if (argc == 1) {
		puts("Будь ласка, введіть шлях до файлу, де зберігаються контакти.");
		scanf_s("%s", pytfiles, N);
		if (openFile("r", pytfiles) == NULL) {
			exit(1);
		}
	}
	else if (argc == 2) {
		strcpy_s(pytfiles, sizeof(pytfiles), argv[1]);
		if (openFile("r", pytfiles) == NULL) {
			exit(1);
		}
	}
	fclose(fp);
	do {
		puts("Будь ласка, введіть кількість контактів, для яких буде виділено пам'ять.(рек. більше 30)");
		scanf_s("%d", &luk);
	} while (luk < 1);



	Contact* Contacts;
	Contacts = memory(luk);
	infomemory(Contacts);
	int c;
	int coun = 0;
	do {
		coun = scanContact(Contacts, pytfiles, luk);
		printf("\nМеню телефонної книги:\n");
		printf("1. Додати контакт\n");
		printf("2. Показати інформацію про контакт\n");
		printf("3. Редагувати інформацію контакту\n");
		printf("4. Видалити контакт\n");
		printf("5. Пошук контакту\n");
		printf("6. Сортурування контакту (за прізвищем)\n");
		printf("0. Вихід\n");
		printf("Виберіть опцію: ");
		scanf_s("%d", &c);
		switch (c)
		{
		case 0: return 0; break;
		case 1:
			if (luk == coun) {
				printf("\nПомилка: ви виділили пам'ять тільки для %d контактів, тому додавання більшої кількості неможливе,\nкраще перезапустіть програму і введіть більше число для розподілу пам'яті.\n", luk);
			}
			else {
				addContact(Contacts, coun, pytfiles);
			}
			break;
		case 2:
			infoContact(Contacts, coun);
			break;
		case 3:
			editContact(coun, Contacts, pytfiles);
			break;
		case 4:
			deleteContact(Contacts, coun, pytfiles);
			break;
		case 5:
			searchContact(Contacts, coun);
			break;
		case 6:
			sortContact(Contacts, coun);
			break;
		default:
			printf("Неправильний вибір номера меню\n");
			break;
		}
	} while (c != 0);
	free(Contacts); // Звільнення пам'яті, виділеної для масиву контактів
	return 0;
}


