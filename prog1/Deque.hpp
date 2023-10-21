#include <string.h>
#ifndef GUARD		
#define GUARD

#define Deque_DEFINE(t)		\
				\
				\
struct Deque_##t##_Iterator{	\
  int id;			\
  t* itt;			\
  t& (*deref)(Deque_##t##_Iterator* it);	\
				\
  int (*inc)(Deque_##t##_Iterator* it);		\
			\
  int (*dec)(Deque_##t##_Iterator* it);		\
				\
};				\
				\
				\
struct Deque_##t {		\
  int id;			\
  Deque_##t##_Iterator* iter;	\
  Deque_##t##_Iterator* iterE;	\
  t* arr = new t[5000];				\
  /*Deque_##t(const Deque_##t &copy) {id = copy.id; iter = copy.iter; iterE = copy.iterE; arr = copy.arr;}*/ 				\
				\
  /*bool equal(const MyClass& ob1, const MyClass& ob2){		\
  if(ob1.id != ob2.id){			\
    return true;		\
  }				\
  for(int i =0; i<10; i++){	\
    if(ob1.name[i]!=ob2.name[i]){	\
      return true;		\
    }				\
  }				\
    return false;			\
  }*/				\
				\
  Deque_##t##_Iterator (*begin)(Deque_##t* deq);	\
		 					\
  Deque_##t##_Iterator (*end)(Deque_##t* deq);		\
				\
  t& (*at)(Deque_##t* deq, int i);		\
				\
  t (*pop_back)(Deque_##t *deq);	\
  t (*pop_front)(Deque_##t *deq);		\
				\
  t (*push_back)(Deque_##t* deq, t item);		\
				\
  t (*push_front)(Deque_##t* deq, t item);	\
				\
  t& (*front)(Deque_##t* deq);	\
				\
  t& (*back)(Deque_##t* deq);		\
				\
  size_t (*size)(Deque_##t* deq);	\
				\
  bool (*empty)(Deque_##t *deq);	\
				\
  bool sort(Deque_##t *, Deque_##t##_Iterator, Deque_##t##_Iterator);	\
								\
  void (*clear)(Deque_##t *deq);				\
					\
  void (*dtor)(Deque_##t *deq);					\
				\
  bool (*compa)(const t&,const t&);				\
				\
				\
  char type_name[sizeof("Deque_" #t)] = "Deque_" #t;/*		*/\
};			\
				\
  t& Deque_##t##_deref(Deque_##t##_Iterator* it){		\
    return *(it->itt);						\
  }				\
  int Deque_##t##_inc(Deque_##t##_Iterator* it){		\
    it->itt++;		\
    return 0;		\
  }			\
  int Deque_##t##_dec(Deque_##t##_Iterator* it){		\
    it->itt--;					\
    return 0;						\
  }						\
  Deque_##t##_Iterator Deque_##t##_begin(Deque_##t* deq){		\
    return *deq->iter;							\
  }							\
  Deque_##t##_Iterator Deque_##t##_end(Deque_##t* deq){		\
    return *deq->iterE;					\
  }							\
  t& Deque_##t##_at(Deque_##t* deq, int i){	\
    return *(deq->iter->itt + i);	\
  }				\
  t Deque_##t##_pop_back(Deque_##t *deq){	\
    t backElement = deq->back(deq);				\
    deq->iterE->itt--;				\
    return backElement;				\
  }				\
  t Deque_##t##_pop_front(Deque_##t *deq){	\
    t frontElement = deq->front(deq);				\
    deq->iter->itt++;						\
    return frontElement;				\
  }				\
  t Deque_##t##_push_back(Deque_##t* deq, t item){	\
    if(deq->size(deq)==0){				\
      *(deq->iterE->itt)=item;			\
      deq->iterE->itt++;				\
      return item;				\
    }else{						\
      *(deq->iterE->itt) = item;			\
      deq->iterE->itt++;				\
      return item;		\
    }				\
  }				\
  t Deque_##t##_push_front(Deque_##t* deq, t item){		\
    if(deq->size(deq)==0){				\
      *(deq->iter->itt)=item;			\
      deq->iterE->itt++;				\
      return item;						\
    }else{						\
      deq->iter->itt--;					\
      *(deq->iter->itt) = item;				\
      return item;					\
    }							\
  }	\
  t& Deque_##t##_front(Deque_##t* deq){	\
    return *(deq->iter->itt);			\
  }		\
  t& Deque_##t##_back(Deque_##t* deq){		\
    return *(deq->iterE->itt - 1);				\
  }				\
  size_t Deque_##t##_size(Deque_##t* deq){		\
    size_t size=0;		\
    for(t* it = deq->iter->itt; it < deq->iterE->itt; it++){	\
      size++;							\
    }				\
    return size;		\
  }		\
  bool Deque_##t##_empty(Deque_##t *deq){	\
    if(deq->size(deq)==0){		\
        return true;					\
    }						\
    return false;				\
  }				\
  void Deque_##t##_clear(Deque_##t *deq){					\
    deq->iter->itt = (deq->arr)+2500;		\
    deq->iterE->itt = deq->iter->itt;						\
    return;				\
  }				\
  void Deque_##t##_dtor(Deque_##t *deq){		\
    delete deq->arr;				\
    delete deq->iter;				\
    delete deq->iterE;				\
    return;					\
  }								\
				\
bool Deque_##t##_ctor(Deque_##t* deq, bool (&comp)(const t&,const t&)){	\
  deq->iter = new Deque_##t##_Iterator;			\
  deq->iter->itt = (deq->arr)+2500;				\
  deq->iterE = new Deque_##t##_Iterator;			\
  deq->iterE->itt = deq->iter->itt;						\
  /*deq->iterE->itt++;*/					\
  deq->compa = &comp;					\
  deq->dtor = &Deque_##t##_dtor;					\
  deq->clear = &Deque_##t##_clear;			\
  deq->empty = &Deque_##t##_empty;			\
  deq->size = &Deque_##t##_size;			\
  deq->back = &Deque_##t##_back;			\
  deq->front = &Deque_##t##_front;			\
  deq->push_front = &Deque_##t##_push_front;		\
  deq->push_back = &Deque_##t##_push_back;		\
  deq->pop_front = &Deque_##t##_pop_front;		\
  deq->pop_back = &Deque_##t##_pop_back;		\
  deq->at = &Deque_##t##_at;				\
  deq->end = &Deque_##t##_end;				\
  deq->begin = &Deque_##t##_begin;			\
  deq->iter->dec = &Deque_##t##_dec;			\
  deq->iterE->dec = &Deque_##t##_dec;			\
  deq->iter->inc = &Deque_##t##_inc;			\
  deq->iterE->inc = &Deque_##t##_inc;			\
  deq->iter->deref = &Deque_##t##_deref;		\
  deq->iterE->deref = &Deque_##t##_deref;		\
  return true;						\
}						\
						\
bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2){		\
  if(deq1.size(&deq1)!=deq2.size(&deq2)){			\
    return false;						\
  }								\
  int i = 0;								\
  for(t* it = deq1.iter->itt; it < deq1.iterE->itt; it++){	\
    if((deq1.compa(deq1.at(&deq1,i), deq2.at(&deq2,i))) || (deq1.compa(deq2.at(&deq1,i), deq1.at(&deq2,i)))){			\
      return false;							\
    }			\
    i++;							\
  }								\
  return true;							\
}								\
								\
bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it1, Deque_##t##_Iterator it2){	\
  return it1.itt == it2.itt;						\
}						\

#endif /* GUARD */
