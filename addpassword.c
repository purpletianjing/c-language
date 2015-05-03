#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int password = 123456;

void printMenu();
int checkType(int type);
int SecretFile(char *sourceFile,char *secretKey,char *targetFile);
char redo();

int main()
{
	char c;
	int newPwd,newRepeatPwd;
	char sourceFile[30],targetFile[30],secretKey[21],action;
	if(!checkType(1))	{
		printf("抱歉，3次输入密码有错。按任意键退出……\n");
		getchar();
		scanf("%c",&c);
		exit(1);
	}

	while(1)	{
		//system("cls");//清屏
		printMenu();
		printf("请输入你的选项：");
		getchar();
		scanf("%c",&action);
		fflush(stdin);
		//system("cls");
		switch(action)	{
			case 'q':
				exit(0);
				break;
			case 'a':
				while(1)	{
					printf("输入要加密的文件:");
					scanf("%s",sourceFile);
					fflush(stdin);
					printf("输入密钥：");
					scanf("%s",secretKey);
					printf("输入加密后的文件：");
					fflush(stdin);
					scanf("%s",targetFile);
					if(SecretFile(sourceFile,secretKey,targetFile))	{
						printf("文件【%s】加密成功，加密后的文件名【%s】\n",sourceFile,targetFile);

					}
					if(redo() == 'a')	{
						system("cls");
					}
					else	{
						break;
					}
				}
				break;
			case 'b':
				while(1)	{
					printf("输入要解密的文件：");
					scanf("%s",sourceFile);
					fflush(stdin);
					printf("输入密钥：");
					scanf("%s",secretKey);
					fflush(stdin);
					printf("输入解密后的文件：");
					scanf("%s",targetFile);
					if(SecretFile(sourceFile,secretKey,targetFile)) {
						printf("文件【%s】解密成功，解密后的文件名【%s】\n",sourceFile,targetFile);

					}
					if(redo() == 'a')	{
						//system("cls");
					}
					else	{
						break;
					}
				}
				break;
			case 'c':
				while(1)	{
					if(!checkType(2))	{
						printf("旧密码验证错误!\n");
						printMenu();
						break;
					}
					printf("请输入新密码：");
					scanf("%d",&newPwd);
					while(1)	{
						if(newPwd >= 1000000)	{
							printf("密码应该为六位数字,请重新输入：");
							scanf("%d",&newPwd);
						}
						else	{
							break;
						}
					}
					fflush(stdin);
					printf("请再次输入新密码：");
					scanf("%d",&newRepeatPwd);
					if(newPwd == newRepeatPwd)	{
						password = newPwd;
						printf("密码修改成功！\n");
					}
					else	{
						printf("两次输入密码不同，修改失败！\n");
					}
					if(redo() == 'a')	{
						system("cls");
					}
					else	{
						break;
					}
				}
			
					break;
				default:
					printf("没有你输入的选项,按任意键回到主菜单\n");
					getchar();
					break;
				
			}
	}
	return 0;

}

void printMenu()
{
	printf("---------欢迎使用改密系统----------------\n");
	printf("                                         \n");
	printf("---------a. 文 件 加 密 -----------------\n");
	printf("---------b. 文 件 解 密 -----------------\n");
	printf("---------c. 修 改 密 码 -----------------\n");
	printf("---------q.   退   出   -----------------\n");
	printf("--                                     --\n");

}

int checkType(int type)
{
	int i = 1;
	int times = 3;
	int pwd;
	if(type == 1)	{
		printf("用户输入了密码，请输入验证：");
	}
	else	{
		printf("用户需要重置密码，请输入验证：");
	}
		for(;i <= times;i++)	{
			fflush(stdin);
			scanf("%d",&pwd);
			if(pwd == password)	{
				return 1;
			}
			if(i < times)	{
				printf("密码错误，请重新输入：");
			}
		}
	return 0;
}

int SecretFile(char *sourceFile,char *secretKey,char *targetFile)
{
	FILE *soufp = NULL;
	FILE *tarfp = NULL;
	char buff[256] = {0};
	int ret = 0;
	int i = 0;
	if((soufp = fopen(sourceFile,"r")) == NULL)	{
		perror("fopen sourceFile:");
		return 0;
	}
	if((tarfp = fopen(targetFile,"w")) == NULL)	{
		perror("fopen targetFile:");
		return 0;
	}

	while((ret = fread(buff,1,sizeof(buff),soufp)) > 0)	{
		for(;i < ret;i++)	{
			buff[i] ^= secretKey[i];
		}
		fwrite(buff,1,ret,tarfp);

	}
	fclose(soufp);
	fclose(tarfp);
	return 1;
}

char redo()
{
	char action;
	printf("接下来你希望做什么？\n");
	printf("a.继续改操作\n");
	printf("b.返回主菜单\n");
	while(1)	{
		fflush(stdin);
		getchar();
		scanf("%c",&action);
		if(action != 'a' && action != 'b')	{
			printf("对不起，没有您的选择，请重新选择！\n");
		}
		else	{
			return action;
		}
	}
}
