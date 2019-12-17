//
//  main.c
//  AED
//
//  Created by Nickson Kley Gonçalves Da Silva on 09/12/19.
//  Copyright © 2019 Nickson Kley Gonçalves Da Silva. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Pdv{

	int index;

	int agility;

	double finalTime;

	double maxTimeAtend;
	double mediaTimeAtend;

	double maxTimeWait;
	double mediaTimeWait;

	double sumTime;
	double maxTime;

	int attendedPeoples;

	double pdvSumTime;
	double pdvMaxTime;

}Pdv;





typedef struct Element{

	void *value;

	struct Element *previous;
	struct Element *next;

}Element;

typedef struct List{

	int count;

	Element *first;
	Element *last;

}List;

List* createList(){

	List *list = malloc(sizeof(List));

	list->count = 0;
	list->first = NULL;
	list->last = NULL;

	return list;

}

void append(void *value, List *list){

	if(list->first == NULL){

		Element *element = malloc(sizeof(Element));

		element->value = value;

		element->previous = NULL;
		element->next = NULL;

		list->first = element;
		list->last = element;
		list->count = 1;

	}else{

		Element *element = malloc(sizeof(Element));

		element->value = value;

		element->previous = list->last;
		element->next = NULL;

		list->last->next = element;

		list->last = element;
		list->count++;

	}

}






int main(){

	//MARK: - leitura dos pdvs antigos
	List *pastFaPdvs = createList();
	int pastAmountPdv;

	scanf("%d", &pastAmountPdv);

	for(int i=0;i < pastAmountPdv;i++){

		int Fa;

		scanf("%d", &Fa);

		Pdv *pastPdvs = malloc(sizeof(Pdv));
		pastPdvs->agility = Fa;
		pastPdvs->attendedPeoples = 0;
		pastPdvs->index = i;
		pastPdvs->maxTimeAtend = 0;
		pastPdvs->maxTimeWait = 0;
		pastPdvs->mediaTimeAtend = 0;
		pastPdvs->mediaTimeWait = 0;
		pastPdvs->finalTime = 0;
		pastPdvs->sumTime = 0;
		pastPdvs->maxTime = 0;
		pastPdvs->pdvSumTime = 0;
		pastPdvs->pdvMaxTime = 0;

		append(pastPdvs,pastFaPdvs);

		//        printf("%f  %d\n", pastPdvs->agility, pastPdvs->index);

	}

	//MARK: - leitura dos pdvs novos
	List *newFaPdvs = createList();
	int newAmountPdv;

	scanf("%d", &newAmountPdv);

	for(int i=0;i < newAmountPdv;i++){

		int Fa;

		scanf("%d", &Fa);

		Pdv *newPdv = malloc(sizeof(Pdv));
		newPdv->agility = Fa;
		newPdv->attendedPeoples = 0;
		newPdv->index = i;
		newPdv->maxTimeAtend = 0;
		newPdv->maxTimeWait = 0;
		newPdv->mediaTimeAtend = 0;
		newPdv->mediaTimeWait = 0;
		newPdv->finalTime = 0;
		newPdv->sumTime = 0;
		newPdv->maxTime = 0;
		newPdv->pdvSumTime = 0;
		newPdv->pdvMaxTime = 0;

		append(newPdv,newFaPdvs);

		//        printf("%f  %d\n", newPdv->agility, newPdv->index);

	}

	//MARK: - criando uma lista com todos os pdv

	List *allPdvs = malloc(sizeof(List));

	Element *caminhador = pastFaPdvs->first;

	while(caminhador != NULL){

		Pdv *pdv = (Pdv *)caminhador->value;

		append(pdv, allPdvs);

		//		printf("%d\n", pdv->index);

		caminhador = caminhador->next;

	}

	Element *newCaminhador = newFaPdvs->first;

	while(newCaminhador != NULL){

		Pdv *pdv = (Pdv *)newCaminhador->value;

		pdv->index = allPdvs->count;

		append(pdv, allPdvs);


		//		printf("%d\n", pdv->index);

		newCaminhador = newCaminhador->next;

	}

	//MARK: - leitura dos fatores de agilidade

	int mediaFA;
	scanf("%d",&mediaFA);

	//MARK: - multiplicando todos os fatores

	Element *allCaminhador = allPdvs->first;

	while(allCaminhador != NULL){

		Pdv *pdv = (Pdv *)allCaminhador->value;

		//		printf("%d\n", pdv->agility);


		pdv->agility *= mediaFA;

		//		printf("%d\n", pdv->agility);

		if(allCaminhador->next != NULL){
			allCaminhador = allCaminhador->next;
		} else{
			break;
		}
	}


	int esperaT2, esperaFilaT3, esperaAtendimentoT3;

	scanf("%d %d %d", &esperaT2, &esperaFilaT3, & esperaAtendimentoT3);

	//MARK: - Produtos desperdicados

	int type2 = 0, type3 = 0;

	//MARK: - Leitura de eventos
	char inputEvent;

	do{
		scanf("%c ", &inputEvent);
		switch(inputEvent){
		case 'C':
			{
				double timeEventC;
				Pdv *minorTimeAttending = NULL;
				int itensCountC, clientTypeC, timeToPayC;

				scanf("%lf %d %d %d", &timeEventC, &itensCountC, &clientTypeC, &timeToPayC);

				timeToPayC *= 1000;

				Pdv *first = (Pdv *)allPdvs->first->value;

				double minTimeValue = first->agility * itensCountC + timeToPayC;

				Element *caminhador = allPdvs->first;

				while (caminhador != NULL) {
					Pdv *atual = (Pdv *)caminhador->value;

					if((atual->agility * itensCountC + timeToPayC) <= minTimeValue && atual->finalTime <= timeEventC){
						minTimeValue = atual->agility * itensCountC + timeToPayC;
						minorTimeAttending = atual;
					}

					caminhador = caminhador->next;
				}

				if(minorTimeAttending == NULL){

					minorTimeAttending = first;

					Element *caminhadorInterno = allPdvs->first;

					while (caminhadorInterno != NULL) {

						Pdv *timeComparison = caminhadorInterno->value;

						if(minorTimeAttending->finalTime > timeComparison->finalTime){

							minorTimeAttending = timeComparison;

						}

						caminhadorInterno = caminhadorInterno->next;

					}

				}

				if(timeEventC - minorTimeAttending->finalTime > 0){

					if(minTimeValue > esperaAtendimentoT3 && clientTypeC ==3){

						minorTimeAttending->finalTime += esperaAtendimentoT3;
						type3 += itensCountC;

						break;

					}

					minorTimeAttending->finalTime += minTimeValue + (timeEventC - minorTimeAttending->finalTime);

				}
				else if(timeEventC - minorTimeAttending->finalTime == 0){

					if(minTimeValue > esperaAtendimentoT3 && clientTypeC ==3){

						minorTimeAttending->finalTime += esperaAtendimentoT3;
						type3 += itensCountC;

						break;

					}

					minorTimeAttending->finalTime += minTimeValue;

				}
				else{

					if((minorTimeAttending->finalTime - timeEventC) > esperaFilaT3 && clientTypeC == 3){

						type3 += itensCountC;

						break;

					}

					if(minTimeValue > esperaAtendimentoT3 && clientTypeC ==3){

						minorTimeAttending->finalTime += esperaAtendimentoT3;

						type3 += itensCountC;

						break;

					}

					minorTimeAttending->finalTime += minTimeValue;

				}

				if(minorTimeAttending->finalTime == minTimeValue){

					minorTimeAttending->finalTime += timeEventC;

				}

				if((minorTimeAttending->finalTime - timeEventC) > esperaT2 && clientTypeC == 2){

					minorTimeAttending->finalTime -= ((minorTimeAttending->finalTime - timeEventC) - esperaT2);

					type2 += itensCountC;

					break;

				}

				minorTimeAttending->attendedPeoples++;
				printf("%d       %f      %f\n", minorTimeAttending->index, timeEventC,minorTimeAttending->finalTime);

				minorTimeAttending->sumTime += minTimeValue;
				if(minTimeValue > minorTimeAttending->maxTime){

					minorTimeAttending->maxTime = minTimeValue;

				}

				minorTimeAttending->pdvSumTime += (minorTimeAttending->finalTime - timeEventC);
				if((minorTimeAttending->finalTime - timeEventC) > minorTimeAttending->pdvMaxTime){
					minorTimeAttending->pdvMaxTime = (minorTimeAttending->finalTime - timeEventC);
				}


				break;
			}

		case 'S':
			{
				double timeEventS;
				int index, timeStop;
				scanf("%lf %d %d",&timeEventS,&index,&timeStop);

				index-=1;

				Element * caminhador = allPdvs->first;
				Pdv * real = NULL;

				while (caminhador != NULL) {

					Pdv *pdv = caminhador->value;

					if (pdv->index == index){

						real = pdv;

						break;

					}

					caminhador = caminhador->next;

				}

				if(real == NULL){

					printf("deu bosta\n");

				}
				else{

					if((real->finalTime - timeEventS) > 0){

						double value = timeStop * 60;
						double mileseconds = value * 1000;

						if((mileseconds - (real->finalTime - timeEventS))>=0){

							real->finalTime += (mileseconds - (real->finalTime - timeEventS));

						}

					}
					else if((real->finalTime - timeEventS) == 0){

						double value = timeStop * 60;
						double mileseconds = value * 1000;

						real->finalTime += mileseconds;

					}
					else{

						double value = timeStop * 60;
						double mileseconds = value * 1000;

						if((mileseconds - (real->finalTime - timeEventS))>=0){

							real->finalTime += (mileseconds +(timeEventS - real->finalTime));

						}

					}

				}

				break;
			}
		}
	}while (inputEvent != 'F');

	Element *medias = allPdvs->first;

	printf("\n-------------------media de atendimento--------------");

	while (medias != NULL) {

		Pdv *pdv = medias->value;

		double coisa = pdv->sumTime/pdv->attendedPeoples;

		printf("\nPDV: %d; media: %lf; max: %lf",pdv->index+1,coisa,pdv->maxTime);

		medias = medias->next;
	}

	printf("\n-------------------media de PDV--------------");

	medias = allPdvs->first;

	while (medias != NULL) {

		Pdv *pdv = medias->value;

		double coisa = pdv->pdvSumTime/pdv->attendedPeoples;

		printf("\nPDV: %d; media: %lf; max: %lf",pdv->index+1,coisa,pdv->pdvMaxTime);

		medias = medias->next;
	}

	printf("\n------------------------droped itens-------------------");
	printf("\ntipo 2: %d",type2);
	printf("\ntipo 3: %d", type3);

	return 0;

}
