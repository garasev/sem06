; Написать функцию, которая выбирает из заданного списка только те числа, которые больше 1 и меньше 10.
(defun find-num (lst) 
(remove-if-not (lambda (a) (and (< a 10) (> a 1))) lst))

; Декартово произведение
(defun decart (lstX lstY)
(mapcan #'(lambda (x)
          (mapcar #'(lambda (y)
                    (list x y)) lstY)) lstX))

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
 