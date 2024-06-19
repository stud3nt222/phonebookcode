#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50

// ��������� ��� ��������� ��������� ����������
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
FILE* fp; // �������� �� ����

// ������� �������
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

// ������� �������� ���'�� ��� ������ ��������
Contact* memory(int luk) {
	Contact* massive = (Contact*)malloc(luk * sizeof(Contact));
	if (massive == NULL) {
		return NULL;
	}
	else {

		return massive;
	}
}

// ������� ��� �������� �������� ���'��
void infomemory(Contact* Contacts)
{
	if (Contacts == NULL) {
		printf("������ ��������� ����� �� ��� ���������!\n");
	}
	else {
		printf("���'��� ��� ���������� ������ ���� ����������!\n");
	}
}

// ������� ��� ����������� ��������
void editContact(int coun, Contact* Contacts, char pytfiles[])
{
	if (coun == 0) {
		printf("�������� ����\n");
	}
	else {
		printf("������ ������ ��������, ���� ������ ����������: ");
		int m = -1, cd;
		int b;
		scanf_s("%d", &cd);
		for (int c = 0; c < coun; c++) {
			if (Contacts[c].num == cd) {
				m = c;
			}
		}
		if (m == -1) {
			printf("����������� ������ ��������.\n");
		}
		else {
			do {
				printf("\n������ ���� ��� �����������:\n");
				printf("1. ����� ��������\n");
				printf("2. �������\n");
				printf("3. ����� 1\n");
				printf("4. ����� 2\n");
				printf("5. ̳��� ������\n");
				printf("6. ���������� ������\n");
				printf("0. ��������� �����������\n");
				printf("������� �����: ");
				scanf_s("%d", &b);
				switch (b) {
				case 1:
					printf("\n������ ����� ��������: ");
					scanf_s("%s", Contacts[m].phoneNumber, N);
					break;
				case 2:
					printf("������ �������: ");
					scanf_s("%s", Contacts[m].lastname, N);
					break;
				case 3:
					printf("������ ����� ����� 1 (������, �����������, ����): ");
					scanf_s("%s", Contacts[m].groups, N);
					break;
				case 4:
					printf("������ ����� ����� 2 (������, �����������, ����): ");
					scanf_s("%s", Contacts[m].groups2, N);
					break;
				case 5:
					printf("������ ���� ������: ");
					scanf_s("%s", Contacts[m].workplace, N);
					break;
				case 6:
					printf("������ ���������� ������: ");
					scanf_s("%s", Contacts[m].email, N);
					break;
				default:
					if (b != 0) {
						printf("������������ ���� ������ ����\n");
					}
					break;
				}
			} while (b != 0);
			openFile("w+", pytfiles); // ����� �������� � ����
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

// ������� ��� �������� �����
int openFile(const char mode[], const char file[])
{
	fopen_s(&fp, file, mode);
	if (!fp)
	{
		puts("�� ������� ������� ���� \n");
		return 0;
	}
	else
		return 1;

}

// ������� ��� ���������� �������� � �����
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

// ������� ��� ��������� ��������
int addContact(Contact* Contacts, int coun, char pytfiles[]) {
	int cus = 0;
	char c[N];

	for (int l = 0; l < coun; l++) {
		if (Contacts[l].num > cus) {
			cus = Contacts[l].num;
		}
	}
	Contacts[coun].num = cus + 1;
	printf("\n������ ����� �������� (����'������): ");
	scanf_s("%s", Contacts[coun].phoneNumber, N);
	printf("������ ������� (����'������): ");
	scanf_s("%s", Contacts[coun].lastname, N);
	do {
		printf("������ ����� 1 (������, �����������, ���� ��� 1 ��� ��������): ");
		scanf_s("%s", c, N);
		if (strstr("-", c) != NULL) {
			puts("�������� '-' ���������, ������� �� ���������� ������� ����. ���� �����, ������ ���� ��������:");
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
		printf("������ ����� 2 (������, �����������, ���� ��� 1 ��� ��������): ");
		scanf_s("%s", c, N);
		if (strstr("-", c) != NULL) {
			puts("�������� '-' ���������, ������� �� ���������� ������� ����. ���� �����, ������ ���� ��������:");
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
		printf("������ ���� ������ (��� 1 ��� ��������): ");
		scanf_s("%s", c, N);
		if (strstr("-", c) != NULL) {
			puts("�������� '-' ���������, ������� �� ���������� ������� ����. ���� �����, ������ ���� ��������:");
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
		printf("������ ��. ������ (��� 1 ��� ��������): ");
		scanf_s("%s", c, N);
		if (strstr("-", c) != NULL) {
			puts("�������� '-' ���������, ������� �� ���������� ������� ����. ���� �����, ������ ���� ��������:");
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

// ������� ��� ��������� ���������� ��� ��������
int infoContact(Contact* Contacts, int coun) { 
	if (coun == 0) {
		printf("�������� ���� \n");
	}
	else {
		printf("\n���������� ��� �������:\n");
		printf("|� ��������|  ����� ��������  |   �������    |             �����             |    ̳��� ������    |     ��. ������ \n");
		for (int i = 0; i < coun; i++) {
			printf("| �%5d   |%18s| %14s| %13s   %13s | %18s | %10s \n", Contacts[i].num, Contacts[i].phoneNumber, Contacts[i].lastname, Contacts[i].groups, Contacts[i].groups2, Contacts[i].workplace, Contacts[i].email);
		}
		fclose(fp);
	}
}

//������� ��� ��������� ��������
int deleteContact(Contact* Contacts, int coun, char pytfiles[]) {
	if (coun == 0) {
		printf("�������� ����\n");
	}
	else {
		printf("������ ������ ��������, ���� ������ ��������: ");
		int v;
		int i = -1;
		scanf_s("%d", &v);
		for (int m = 0; m < coun; m++) {
			if (Contacts[m].num == v) {
				i = m;
			}
		}
		if (i == -1) {
			printf("����������� ������ ��������.\n");
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

// ������� ��� ������ ��������
void searchContact(Contact* Contacts, int coun) {
	if (coun == 0) {
		printf("�������� ����\n");
	}
	else {
		printf("\n1) ����� ��������\n");
		printf("2) �������\n");
		printf("3) �����\n");
		printf("4) ̳��� ������\n");
		printf("��� ������ �� ����� ���� ������ 0\n");
		int r, h;
		int v;
		printf("������� ������� ��� ������: ");
		scanf_s("%d", &r);
		switch (r)
		{
		case 1:
			do {
				printf("������ ����� ��������: ");
				char sur[N];
				scanf_s("%s", sur, N);

				int foundPhoneNumber = 0;
				printf("|� ��������|  ����� ��������  |   �������    |             �����             |    ̳��� ������    |     ��. ������ \n");
				for (h = 0; h < coun; h++) {
					if (strstr(Contacts[h].phoneNumber, sur) != NULL) {
						printf("| �%5d   |%18s| %14s| %13s   %13s | %18s | %10s\n", Contacts[h].num, Contacts[h].phoneNumber, Contacts[h].lastname, Contacts[h].groups, Contacts[h].groups2, Contacts[h].workplace, Contacts[h].email);
						foundPhoneNumber = 1;
					}

				}
				if (foundPhoneNumber == 0) {
					printf("������� �� ��������\n");
				}

				printf("\n�� ������ �������� ����� �����? 1 - ��� 0 - �\n");
				scanf_s("%d", &v);
			} while (v != 0);
			break;
		case 2:
			do {
				printf("������ �������: ");
				char sur2[N];
				scanf_s("%s", sur2, N);
				int foundSecondName = 0;
				printf("|� ��������|  ����� ��������  |   �������    |             �����             |    ̳��� ������    |     ��. ������ \n");
				for (h = 0; h < coun; h++) {
					if (strstr(Contacts[h].lastname, sur2) != NULL) {
						printf("| �%5d   |%18s| %14s| %13s   %13s | %18s | %10s\n", Contacts[h].num, Contacts[h].phoneNumber, Contacts[h].lastname, Contacts[h].groups, Contacts[h].groups2, Contacts[h].workplace, Contacts[h].email);
						foundSecondName = 1;
					}
				}
				if (foundSecondName == 0) {
					printf("������� �������� �� ��������\n");
				}

				printf("\n�� ������ �������� ����� �����? 1 - ��� 0 - �\n");
				scanf_s("%d", &v);
			} while (v != 0);
			break;
		case 3:
			do {
				printf("������ ����� (������, �����������, ����): ");
				char sur3[N];
				scanf_s("%s", sur3, N);
				if (strstr("-", sur3) != NULL) {
					printf("����� �������� �� ��������\n");
				}
				else {
					int foundGroup = 0;
					printf("|� ��������|  ����� ��������  |   �������    |             �����             |    ̳��� ������    |     ��. ������ \n");
					for (h = 0; h < coun; h++) {
						if (strstr(Contacts[h].groups, sur3) != NULL || strstr(Contacts[h].groups2, sur3) != NULL) {
							printf("| �%5d   |%18s| %14s| %13s   %13s | %18s | %10s\n", Contacts[h].num, Contacts[h].phoneNumber, Contacts[h].lastname, Contacts[h].groups, Contacts[h].groups2, Contacts[h].workplace, Contacts[h].email);
							foundGroup = 1;
						}
					}
					if (foundGroup == 0) {
						printf("����� �������� �� ��������\n");
					}
				}
				printf("\n�� ������ �������� ����� �����? 1 - ��� 0 - �\n");
				scanf_s("%d", &v);
			} while (v != 0);
			break;
		case 4:
			do {
				printf("������ ���� ������: ");
				char sur4[N];
				scanf_s("%s", sur4, N);
				if (strstr("-", sur4) != NULL) {
					printf("̳��� ������ �������� �� ��������\n");
				}
				else {
					int foundWorkPlace = 0;
					printf("|� ��������|  ����� ��������  |   �������    |             �����             |    ̳��� ������    |     ��. ������ \n");
					for (h = 0; h < coun; h++) {
						if (strstr(Contacts[h].workplace, sur4) != NULL) {
							printf("| �%5d   |%18s| %14s| %13s   %13s | %18s | %10s\n", Contacts[h].num, Contacts[h].phoneNumber, Contacts[h].lastname, Contacts[h].groups, Contacts[h].groups2, Contacts[h].workplace, Contacts[h].email);
							foundWorkPlace = 1;

						}
					}
					if (foundWorkPlace == 0) {
						printf("̳��� ������ �������� �� ��������\n");
					}
				}
				printf("\n�� ������ �������� ����� �����? 1 - ��� 0 - �\n");
				scanf_s("%d", &v);
			} while (v != 0);
			break;
		default:
			printf("������������ ���� ������ ����\n");
		}
	}
}

// ������� ��� ���������� �������� �� ��������
void sortContact(Contact* Contacts, int coun) { 
	char* parr;
	if (coun == 0) {
		printf("�������� ����\n");
	}
	else {
		printf("\n���������� ��� �������:\n");
		printf("|� ��������|  ����� ��������  |   �������    |             �����             |    ̳��� ������    |     ��. ������ \n");
		for (int q = 192; q <= 255; q++) {
			for (int s = 0; s < coun; s++) {
				parr = Contacts[s].lastname;
				if ((char)q == parr[0]) {
					printf("| �%5d   |%18s| %14s| %13s   %13s | %18s | %10s\n", Contacts[s].num, Contacts[s].phoneNumber, Contacts[s].lastname, Contacts[s].groups, Contacts[s].groups2, Contacts[s].workplace, Contacts[s].email);
				}
			}
		}
	}
}

// ������� ������� ��������
int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char pytfiles[N];
	int luk;
	if (argc == 1) {
		puts("���� �����, ������ ���� �� �����, �� ����������� ��������.");
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
		puts("���� �����, ������ ������� ��������, ��� ���� ���� ������� ���'���.(���. ����� 30)");
		scanf_s("%d", &luk);
	} while (luk < 1);



	Contact* Contacts;
	Contacts = memory(luk);
	infomemory(Contacts);
	int c;
	int coun = 0;
	do {
		coun = scanContact(Contacts, pytfiles, luk);
		printf("\n���� ��������� �����:\n");
		printf("1. ������ �������\n");
		printf("2. �������� ���������� ��� �������\n");
		printf("3. ���������� ���������� ��������\n");
		printf("4. �������� �������\n");
		printf("5. ����� ��������\n");
		printf("6. ������������ �������� (�� ��������)\n");
		printf("0. �����\n");
		printf("������� �����: ");
		scanf_s("%d", &c);
		switch (c)
		{
		case 0: return 0; break;
		case 1:
			if (luk == coun) {
				printf("\n�������: �� ������� ���'��� ����� ��� %d ��������, ���� ��������� ����� ������� ���������,\n����� ������������ �������� � ������ ����� ����� ��� �������� ���'��.\n", luk);
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
			printf("������������ ���� ������ ����\n");
			break;
		}
	} while (c != 0);
	free(Contacts); // ��������� ���'��, ������� ��� ������ ��������
	return 0;
}


