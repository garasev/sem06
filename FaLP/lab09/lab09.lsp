; Написать функцию, которая выбирает из заданного списка только те числа, которые больше 1 и меньше 10.
(defun find-num (lst) 
(remove-if-not (lambda (a) (and (< a 10) (> a 1))) lst))

; Декартово произведение
(defun decart (lstX lstY)
(mapcan #'(lambda (x)
          (mapcar #'(lambda (y)
                    (list x y)) lstY)) lstX))
; rec
(defun decart-rec (lstX lstY)
(cond ((null lstX) nil)
	  (T (cons (decart-rec-inner (car lstX) lstY) (decart-rec (cdr lstX) lstY)))))

(defun decart-rec-inner (el lstY)
(cond ((null lstY) nil)
	  (T (cons (cons el (car lstY)) (decart-rec-inner el (cdr lstY))))))

; Пусть list-oflist список, состоящий из списков. Написать функцию, которая вычисляет сумму длин всех элементов list-of-list.
(defun my_len (lst)
(cond ((null lst) 0)
      (t (+ 1 (my_len(cdr lst))))))

(defun len-list-inner (lst len)
(cond ((null lst) len)
      (T (len-list-inner (cdr lst) (+ (my_len (car lst)) len)))))

(defun len-list (lst)
(cond ((null lst) 0)
	  (T (len-list-inner lst 0))))
	  
; Квадраты
(defun squadr (lst)
(mapcar (lambda (a) 
	    (cond ((listp a) (squadr a))
			  ((numberp a) (* a a))
		      (T a))) lst))

(defun sq-rec (lst)
(cond ((null lst) nil)
	  ((listp (car lst)) (cons (sq-rec (car lst)) (sq-rec (cdr lst))))
	  (T (cons (* (car lst) (car lst)) (sq-rec (cdr lst))))))
 
(defun l1 (lst) (level lst nil))
(defun level (lst tail)
(cond ((null lst) tail)
	  ((listp (car lst)) (level (car lst) (level (cdr lst) tail)))
	  (T (cons (car lst) (level (cdr lst) tail)))))
