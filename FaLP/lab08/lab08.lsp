; Умножение, только если все числа.
(defun mulla (lst k)
(and (every #'numberp lst)
	 (mapcar (lambda (a) (* a k)) lst)))

; Умножить все числа.
(defun mullb (lst k)
(mapcar (lambda (a) 
	    (cond ((listp a) (mullb a k))
			  ((numberp a) (* a k))
		      (T a))) lst))

; select-between
(defun select-between (lst a b) 
(reduce (lambda (res tmp)
(cond ((and (> tmp a) (< tmp b)) (append res (list tmp)))
      (T res)))
lst :initial-value Nil))
; sort
(defun my_m (lst m)
(cond ((null lst) m)
	  ((<(car lst) m) (my_m (cdr lst) (car lst)))
	  (T (my_m (cdr lst) m))))

(defun my_min (lst)
(cond ((null lst) Nil)
      (T (my_m (cdr lst) (car lst)))))

(defun my_rem (el lst) 
(cond ((null lst) Nil)
	  (T (reduce (lambda (res tmp)
				 (cond ((= el tmp) res)
					   (T (append res (list tmp)))))
lst :initial-value Nil))))

(defun my_r (el lst res)
(cond ((null lst) res)
	  ((= el (car lst)) (append res (cdr lst)))
	  (T (my_r el (cdr lst) (append res (list (car lst)))))))

(defun my_rem_v2 (el lst) 
(cond ((null lst) Nil)
	  (T (my_r el lst Nil))))
	  
(defun my_s (lst res)
(cond ((null lst) res)
	  (T (my_s (remove (my_min lst) lst) (append res (list (my_min lst)))))))
 
(defun my_sort (lst)
(cond ((null lst) Nil)
	  (T (my_s lst Nil))))
<<<<<<< HEAD
	  
=======

>>>>>>> cada34c1ec8af96c5378ba067382d28f48b9974b
; Все числа на 10 уменьшить.
(defun decr10 (lst)
(mapcar (lambda (a) (- a 10)) lst))

<<<<<<< HEAD

=======
>>>>>>> cada34c1ec8af96c5378ba067382d28f48b9974b
; Поиск первого не пустого списка.
(defun find-list (lst)
(find-if (lambda (a) (and (listp a) (not(null a)))) lst))

<<<<<<< HEAD

; sum 
(defun summa (lst) (summa-inner lst 0))
(defun summa-inner (lst res)
(reduce (lambda (res a) 
	    (cond ((listp a) (summa-inner a res))
			  ((numberp a) (+ res a))
			  (T res))) lst :initial-value res))
			  
; for lab09
(defun squadr (lst)
(mapcar (lambda (a) 
	    (cond ((listp a) (squadr a))
			  ((numberp a) (* a a))
		      (T a))) lst))

; for lab10
(defun select-odd (lst)
(reduce (lambda (res a) 
		(cond ((and (numberp a) (oddp a)) (append res (list a)))
			  (T res))) lst :initial-value Nil))

(defun select-even (lst)
(reduce (lambda (res a) 
		(cond ((and (numberp a) (evenp a)) (append res (list a)))
			  (T res))) lst :initial-value Nil))

(defun sum-all-odd (lst)
(reduce (lambda (res a) 
		(cond ((and (numberp a) (oddp a)) (+ res a))
			  (T res))) lst :initial-value 0))

(defun sum-all-even (lst)
(reduce (lambda (res a) 
		(cond ((and (numberp a) (evenp a)) (+ res a))
			  (T res))) lst :initial-value 0))

(defun cons-squad (lst)
(cond ((null lst) Nil)
	  (T (cons (* (car lst) (car lst)) (cons-squad (cdr lst))))))
=======
; sum
(defun summa (lst) (summa-inner lst 0))
(defun summa-inner (lst res)
(reduce (lambda (res a)
		(cond ((listp a) (summa-inner a res))
			  ((numberp a) (+ res a))
			  (T res))) 
		lst :initial-value res))
>>>>>>> cada34c1ec8af96c5378ba067382d28f48b9974b
