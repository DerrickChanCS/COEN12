#include <stdio.h>
#include <stdlib.h>

long long comb(int monsters, int skills);
long double noSkill(int loop);
long double yesSkill(int loops);

int main()
{
	int monsters;
	int skills;
	printf("How many monsters do you have?: " );
	scanf("%i", &monsters);
	printf("How many skillups do you want?: ");
	scanf("%i", &skills);

	long long combinations = comb(monsters, skills);
	
//	printf("Done with comb");
	long double answer = 0;
	for(int i = skills; i <= monsters; i++)
	{
		answer += noSkill(monsters - i) * yesSkill(i) * comb(monsters, i);	
		printf("%Lf answer\n", answer);
	}
	answer *= 100;
		
//	double answer = noSkill*yesSkill*combinations*100;
	//printf("%f noSkill\n", noSkill);
	//printf("%f yesSkill\n", yesSkill);
	
	printf("You have a %Lf%% chance to get at least  %i skillups out of %i monsters\n", answer, skills, monsters);

	return -1;
}

long double noSkill(int loop)
{
	long double answer = 1;
	for(int i = 0; i < loop; i++)
	{
		answer *= .8;
	}
	return answer;
}

long double yesSkill(int loop)
{
	long double answer = 1;
	for(int i = 0; i < loop; i++)
	{
		answer *= .2;
	}
	return answer;
}

long long comb(int monsters, int skills)
{
//	printf("%i monsters\n", monsters);

//	printf("%i skills\n", skills);
	if(skills == monsters)
		return 1;
//	printf("%i monsters\n", monsters);

//	printf("%i skills\n", skills);
	long long answer = 1;
	for(int i=monsters - skills; i < monsters; i++)
	{
	//	printf("%i index:", i);
	//	printf("in the for");
	//	printf("%llu * %i \n", answer, i+1);
		answer= answer*(i+1);
	//	printf("%llu answer\n", answer);
	}	
	//printf("%llu answer\n", answer);

	long long factorial = 1;
	for(int i = 1; i < skills; i++)
	{
		factorial = factorial *(i+1);
	}
	//printf("%llu factorial\n", factorial);
	return answer/factorial;
}
