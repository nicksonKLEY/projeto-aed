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

	float finalTime;

    float maxTimeAtend;
    float mediaTimeAtend;

    float maxTimeWait;
    float mediaTimeWait;

    int attendedPeoples;

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






typedef int Comparator (void*, void*);

List* createList(){

    List *list = malloc(sizeof(List));

    list->count = 0;
    list->first = NULL;
    list->last = NULL;

    return list;

}

void changeFirst(void *value, List *list){

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

        element->previous = NULL;
        element->next = list->first;

        list->first = element;
        list->count++;

    }

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

void removeFirst(List *list){

    if(list->first != NULL){

        Element*currentFirst = list->first;
        Element*newFirst = currentFirst->next;

        free(currentFirst);

        list->first = newFirst;

        list->count--;

        if(list->first == NULL){

            list->last = NULL;

        }

    }

}

void removeLast(List *list){

    if(list->last != NULL){

        Element*currentLast = list->last;
        Element*newLast = currentLast->previous;

        free(currentLast);

        list->last = newLast;

        list->count--;

        if(list->last == NULL){
            list->first = NULL;
        }

    }

}

List* sort(List*list, Comparator comparator){

    List*result = createList();
    Element *walker = list->first;

    while(walker != NULL){

        Element *previous = NULL;
	    Element *resultWalker = result->first;
	    while ((resultWalker!=NULL) && (comparator(walker, resultWalker) >= 0)){
            previous = resultWalker;
            resultWalker = resultWalker->next;
        }
        if (previous==NULL){
            changeFirst(walker, result);
        } else if(resultWalker == NULL){
            append(walker,result);
        } else {
            Element *elem = malloc(sizeof(Element));
            elem->value = walker;
            elem->next = resultWalker;
            previous->next = elem;
            result->count++;
        }

        walker = walker->next;

    }

    return result;

}

void showAll(List *list){

    Element *current = list->first;

    if(current == NULL){
        printf("lista vazia");
    }
    else{

        do{



            printf("%f\n",*(float*)current->value);

            current = current->next;

        }while(current != NULL);

    }

}

typedef struct Event{

    char typeEvent;
    float timeEvent;
    void *event;

}Event;
typedef struct ArriveClient{

    int itensCount;
    int clientType;
    int timeToPay;

}ArriveClient;
typedef struct PdvSuspension{

    int indexPdv;
    int timeDuration;

}PdvSuspension;
typedef struct Schedule{

    List *events;

}Schedule;

Schedule* createSchedule(){

    Schedule *schedule = malloc(sizeof(Schedule));

    schedule->events = createList();

    return schedule;

}

int comparatorEvents(void*leftEvent,void*rightEvent){

    Event *lEvent = leftEvent;
    Event *rEvent = rightEvent;

    if(lEvent->timeEvent > rEvent->timeEvent){
        return -1;
    }
    else if (lEvent->timeEvent < rEvent->timeEvent){
        return 1;
    }
    else{
        return 0;
    }

}

void showSchedule(Schedule * schedule){

    Element *current = schedule->events->first;

    if(current == NULL){
        printf("lista vazia");
    }
    else{

        do{

            Event currentEvent = *(Event*)current->value;

            printf("%f\n",currentEvent.timeEvent);

            current = current->next;

        }while(current != NULL);

    }

}

// int main(){
//
//     List *pastFaPdvs = createList();
//     int pastAmountPdv;
//
//     scanf("%d", &pastAmountPdv);
//
//     for(int i=0;i < pastAmountPdv;i++){
//
//         float *Fa = malloc(sizeof(float));
//
//         scanf("%f",Fa);
//
//         append(Fa,pastFaPdvs);
//
//     }
//
//     List *newFaPdvs = createList();
//     int newAmountPdv;
//
//     scanf("%d", &newAmountPdv);
//
//     for (int i=0;i<newAmountPdv;i++){
//
//         float *Fa = malloc(sizeof(float));
//
//         scanf("%f",Fa);
//
//         append(Fa,newFaPdvs);
//
//     }
//
//     float mediaTimePerItem;
//
//     scanf("%f", &mediaTimePerItem);
//
//     //valor que guarda quanto tempo os clientes do tipo 2 podem esperar(fila + atendimento)
//     float timeType2;
//
//     //valor que guarda o tempo que o tipo 3 pode esperar na fila
//     float timeLineType3;
//
//     //valor que guarda o tempo que o tipo 3 pode esperar no atendimento
//     float timeAtendType3;
//
//     scanf("%f",&timeType2);
//     scanf("%f",&timeLineType3);
//     scanf("%f",&timeAtendType3);
//
//     char inputEvent;
//
//     Schedule *eventsSchedule = createSchedule();
//
//     //Ler os inputs de Eventos
//     do{
//
//         scanf("%c", &inputEvent);
//
//         switch(inputEvent){
//
//             case 'C':
//                 {
//                     float timeEventC;
//                     int itensCountC, clientTypeC, timeToPayC;
//
//                     scanf("%f %d %d %d", &timeEventC, &itensCountC, &clientTypeC, &timeToPayC);
//
//                     Event *evento = malloc(sizeof(Event));
//
//                     evento->typeEvent = 'C';
//                     evento->timeEvent = timeEventC;
//
//                     ArriveClient  *client = malloc(sizeof(ArriveClient));
//
//                     client->itensCount = itensCountC;
//                     client->clientType = clientTypeC;
//                     client->timeToPay = timeToPayC;
//
//                     evento->event = client;
//
//                     append(evento,eventsSchedule->events);
//
//                     break;
//                 }
//             case 'S':
//                 {
//                     float timeEventS;
//                     int indexPdv, duration;
//
//                     scanf("%f %d %d", & timeEventS, &indexPdv, &duration);
//
//                     Event * evento = malloc(sizeof(Event));
//
//                     evento->typeEvent = 'S';
//                     evento->timeEvent = timeEventS;
//
//                     PdvSuspension *suspension = malloc(sizeof(PdvSuspension));
//
//                     suspension->indexPdv = indexPdv;
//                     suspension->timeDuration = duration;
//
//                     evento->event = suspension;
//
//                     append(evento, eventsSchedule->events);
//
//                     break;
//                 }
//             default:
//                 break;
//
//         }
//
//     }while(inputEvent != 'F');
//     printf("\n\nkbo\n\n");
//     sort(eventsSchedule->events,comparatorEvents);
//     showSchedule(eventsSchedule);
//
//     return 0;
// }




// int main(){
//
//     // List *pastFaPdvs = createList();
//     // int pastAmountPdv;
//
//     // scanf("%d", &pastAmountPdv);
//
//     // for(int i=0;i < pastAmountPdv;i++){
//
//     //     float *Fa = malloc(sizeof(float));
//
//     //     scanf("%f",Fa);
//
//     //     append(Fa,pastFaPdvs);
//
//     // }
//
//     // List *newFaPdvs = createList();
//     // int newAmountPdv;
//
//     // scanf("%d", &newAmountPdv);
//
//     // for (int i=0;i<newAmountPdv;i++){
//
//     //     float *Fa = malloc(sizeof(float));
//
//     //     scanf("%f",Fa);
//
//     //     append(Fa,newFaPdvs);
//
//     // }
//
//
//     float fa[6];
//     fa[0] = 5;
//     fa[1] = 4;
//     fa[2] = 3;
//     fa[3] = 2;
//     fa[4] = 7;
//     fa[5] = 1;
//
//     float finalTime[6];
//     finalTime[0] = 0;
//     finalTime[1] = 0;
//     finalTime[2] = 0;
//     finalTime[3] = 0;
//     finalTime[4] = 0;
//     finalTime[5] = 0;
//
//     int nPDVs = 6;
//
//     float middleTimePDV[6];
//     middleTimePDV[0] = 0;
//     middleTimePDV[1] = 0;
//     middleTimePDV[2] = 0;
//     middleTimePDV[3] = 0;
//     middleTimePDV[4] = 0;
//     middleTimePDV[5] = 0;
//
//     int attendedPeoples[6];
//     attendedPeoples[0] = 0;
//     attendedPeoples[1] = 0;
//     attendedPeoples[2] = 0;
//     attendedPeoples[3] = 0;
//     attendedPeoples[4] = 0;
//     attendedPeoples[5] = 0;
//
//
//     float mediaTimePerItem;
//
//     scanf("%f", &mediaTimePerItem);
//
//     //valor que guarda quanto tempo os clientes do tipo 2 podem esperar(fila + atendimento)
//     float timeType2;
//
//     //valor que guarda o tempo que o tipo 3 pode esperar na fila
//     float timeLineType3;
//
//     //valor que guarda o tempo que o tipo 3 pode esperar no atendimento
//     float timeAtendType3;
//
//     scanf("%f",&timeType2);
//     scanf("%f",&timeLineType3);
//     scanf("%f",&timeAtendType3);
//
//     char inputEvent;
//
//     Schedule *eventsSchedule = createSchedule();
//
//     //Ler os inputs de Eventos
//     do{
//
//         scanf("%c", &inputEvent);
//
//         switch(inputEvent){
//
//             case 'C':
//                 {
//                     float timeEventC;
//                     int itensCountC, clientTypeC, timeToPayC;
//
//                     scanf("%f %d %d %d", &timeEventC, &itensCountC, &clientTypeC, &timeToPayC);
//
//                     int minIndex;
//                     float minTimeValue = fa[0] * mediaTimePerItem * itensCountC + timeToPayC;
//
//                     for(int i = 0; i < nPDVs ; i++){
//                         if(finalTime[i] == 0 && i==0){
//                             minTimeValue = fa[0] * mediaTimePerItem * itensCountC + timeToPayC;
//                             minIndex = 0;
//                         }
//                         if((fa[i] * mediaTimePerItem * itensCountC + timeToPayC) < minTimeValue && finalTime[i] <= timeEventC + (fa[i] * mediaTimePerItem *itensCountC + timeToPayC)){
//                             minTimeValue = fa[i] * mediaTimePerItem *itensCountC + timeToPayC;
//                             minIndex = i;
//                         }
//                     }
//
//                     finalTime[minIndex] += timeEventC + minTimeValue;
//
//                     float timeLine;
//                     float timeAtend = fa[minIndex] * mediaTimePerItem * itensCountC + timeToPayC;
//
//                     if(timeEventC <= finalTime[minIndex]){
//                         timeLine = (finalTime[minIndex] - timeEventC);
//                         switch (clientTypeC)
//                         {
//                         case 2:
//                             if(timeLine + timeAtend > timeType2){
//
//                             }else
//                             {
//                                 finalTime[minIndex] += timeLine + timeAtend;
//                                 middleTimePDV[minIndex] = middleTimePDV[minIndex] + timeAtend;
//                                 attendedPeoples[minIndex]++;
//                             }
//                             break;
//                         case 3:
//                             if(timeLine > timeLineType3 || timeAtend > timeAtendType3){
//
//                             } else
//                             {
//                                 finalTime[minIndex] += timeLine + timeAtend;
//                                 middleTimePDV[minIndex] = middleTimePDV[minIndex] + timeAtend;
//                                 attendedPeoples[minIndex]++;
//                             }
//
//                             break;
//                         default:
//                             break;
//                         }
//                     }else
//                     {
//                         timeLine = 0;
//                         switch (clientTypeC)
//                         {
//                         case 2:
//                             if(timeLine + timeAtend > timeType2){
//
//                             }else
//                             {
//                                 finalTime[minIndex] += timeLine + timeAtend;
//                                 middleTimePDV[minIndex] = middleTimePDV[minIndex] + timeAtend;
//                                 attendedPeoples[minIndex]++;
//                             }
//                             break;
//                         case 3:
//                             if(timeLine > timeLineType3 || timeAtend > timeAtendType3){
//
//                             } else
//                             {
//                                 finalTime[minIndex] += timeLine + timeAtend;
//                                 middleTimePDV[minIndex] = middleTimePDV[minIndex] + timeAtend;
//                                 attendedPeoples[minIndex]++;
//                             }
//
//                             break;
//                         default:
//                             break;
//                         }
//                     }
//
//                     printf("\n%d       %f      %f                  %f", minIndex, timeEventC,finalTime[minIndex], middleTimePDV[minIndex]);
//
//                     Event *evento = malloc(sizeof(Event));
//
//                     evento->typeEvent = 'C';
//                     evento->timeEvent = timeEventC;
//
//                     ArriveClient  *client = malloc(sizeof(ArriveClient));
//
//                     client->itensCount = itensCountC;
//                     client->clientType = clientTypeC;
//                     client->timeToPay = timeToPayC;
//
//                     evento->event = client;
//
//                     append(evento,eventsSchedule->events);
//
//                     break;
//                 }
//             case 'S':
//                 {
//                     float timeEventS;
//                     int indexPdv, duration;
//
//                     scanf("%f %d %d", &timeEventS, &indexPdv, &duration);
//
//                     float timeStand = timeEventS + (duration * 60) - finalTime[indexPdv];
//                     finalTime[indexPdv] += timeStand;
//
//                     printf("\nO PDV %d parou em %f, durante %d segundos.           %f", indexPdv, timeEventS, (duration * 60), finalTime[indexPdv]);
//
//                     Event * evento = malloc(sizeof(Event));
//
//                     evento->typeEvent = 'S';
//                     evento->timeEvent = timeEventS;
//
//                     PdvSuspension *suspension = malloc(sizeof(PdvSuspension));
//
//                     suspension->indexPdv = indexPdv;
//                     suspension->timeDuration = duration;
//
//                     evento->event = suspension;
//
//                     append(evento, eventsSchedule->events);
//
//                     break;
//                 }
//             default:
//                 break;
//
//         }
//
//     }while(inputEvent != 'F');
//
//     for(int i ; i < nPDVs ; i++){
//         // middleTimePDV[i] = middleTimePDV[i]/attendedPeoples[i];
//         printf("\n%f", middleTimePDV[i]);
//     }
//
//
//
//     printf("\n\nkbo\n\n");
//     sort(eventsSchedule->events,comparatorEvents);
//     // showSchedule(eventsSchedule);
//
//     return 0;
// }


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

	//MARK: - Leitura de eventos
	char inputEvent;

	do{
		scanf("%c", &inputEvent);

		switch(inputEvent){
			 case 'C':
				 {
					 float timeEventC;
					 int itensCountC, clientTypeC, timeToPayC;

					 scanf("%f %d %d %d", &timeEventC, &itensCountC, &clientTypeC, &timeToPayC);

					 Pdv *minIndex = malloc(sizeof(Pdv));

					Pdv *first = (Pdv *)allPdvs->first;
					float minTimeValue = first->agility * itensCountC + timeToPayC;

					 Element *caminhador = allPdvs->first;

					 while (caminhador != NULL) {
						 Pdv *atual = (Pdv *)caminhador->value;

						 if(atual->finalTime == 0 && atual->index == 0){
							 minTimeValue = atual->agility * itensCountC + timeToPayC;
							 minIndex = atual;
						 }
						 if((atual->agility * itensCountC + timeToPayC) < minTimeValue && atual->finalTime <= timeEventC + (atual->agility * itensCountC + timeToPayC)){
							 minTimeValue = atual->agility *itensCountC + timeToPayC;
							 minIndex = atual;
						 }

						 if(caminhador->next != NULL){
							 caminhador = caminhador->next;
						 } else{
							 break;
						 }
					 }

					 minIndex->finalTime += timeEventC + minTimeValue;



					 float timeLine;
					 float timeAtend = minIndex->agility * itensCountC + timeToPayC;

					 if(timeEventC <= minIndex->finalTime){
						 timeLine = (minIndex->finalTime - timeEventC);
						 switch (clientTypeC)
						 {
						 case 2:
							 if(timeLine + timeAtend > esperaT2){

							 }else
							 {
								 minIndex->finalTime += timeLine + timeAtend;
//								 middleTimePDV[minIndex] = middleTimePDV[minIndex] + timeAtend;
								 attendedPeoples[minIndex]++;
							 }
							 break;
						 case 3:
							 if(timeLine > timeLineType3 || timeAtend > timeAtendType3){

							 } else
							 {
								 finalTime[minIndex] += timeLine + timeAtend;
								 middleTimePDV[minIndex] = middleTimePDV[minIndex] + timeAtend;
								 attendedPeoples[minIndex]++;
							 }

							 break;
						 default:
							 break;
						 }
					 }else
					 {
						 timeLine = 0;
						 switch (clientTypeC)
						 {
						 case 2:
							 if(timeLine + timeAtend > timeType2){

							 }else
							 {
								 finalTime[minIndex] += timeLine + timeAtend;
								 middleTimePDV[minIndex] = middleTimePDV[minIndex] + timeAtend;
								 attendedPeoples[minIndex]++;
							 }
							 break;
						 case 3:
							 if(timeLine > timeLineType3 || timeAtend > timeAtendType3){

							 } else
							 {
								 finalTime[minIndex] += timeLine + timeAtend;
								 middleTimePDV[minIndex] = middleTimePDV[minIndex] + timeAtend;
								 attendedPeoples[minIndex]++;
							 }

							 break;
						 default:
							 break;
						 }
					 }

					 printf("\n%d       %f      %f                  %f", minIndex, timeEventC,finalTime[minIndex], middleTimePDV[minIndex]);

					 Event *evento = malloc(sizeof(Event));

					 evento->typeEvent = 'C';
					 evento->timeEvent = timeEventC;

					 ArriveClient  *client = malloc(sizeof(ArriveClient));

					 client->itensCount = itensCountC;
					 client->clientType = clientTypeC;
					 client->timeToPay = timeToPayC;

					 evento->event = client;

					 append(evento,eventsSchedule->events);

					 break;
				 }
			 case 'S':
				 {
					 float timeEventS;
					 int indexPdv, duration;

					 scanf("%f %d %d", &timeEventS, &indexPdv, &duration);

					 float timeStand = timeEventS + (duration * 60) - finalTime[indexPdv];
					 finalTime[indexPdv] += timeStand;

					 printf("\nO PDV %d parou em %f, durante %d segundos.           %f", indexPdv, timeEventS, (duration * 60), finalTime[indexPdv]);

					 Event * evento = malloc(sizeof(Event));

					 evento->typeEvent = 'S';
					 evento->timeEvent = timeEventS;

					 PdvSuspension *suspension = malloc(sizeof(PdvSuspension));

					 suspension->indexPdv = indexPdv;
					 suspension->timeDuration = duration;

					 evento->event = suspension;

					 append(evento, eventsSchedule->events);

					 break;
				 }
			 default:
				 break;

		 }

	 }while(inputEvent != 'F');

	 for(int i ; i < nPDVs ; i++){
		 // middleTimePDV[i] = middleTimePDV[i]/attendedPeoples[i];
		 printf("\n%f", middleTimePDV[i]);
	 }



	 printf("\n\nkbo\n\n");
	 sort(eventsSchedule->events,comparatorEvents);
	 // showSchedule(eventsSchedule);

	 return 0;

}
