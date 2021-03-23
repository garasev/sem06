; rec-add
(defun rec-add (lst)
(cond ((null lst) 0)
	  (T (r-add lst 0))))

(defun r-add (lst res)
(cond ((null lst) res)
	  (T (r-add (cdr lst) (+ res (car lst))))))

; rec-nth
(defun rec_nth (lst n)
(cond ((null lst) Nil)
      ((= n 0) (car lst))
	  (T (rec_nth (cdr lst) (- n 1)))))

; alloddr
(defun alloddr (lst)
(cond ((null lst) T)
	  ((oddp (car lst)) (alloddr (cdr lst)))))

; Хвостовая рекурсия - ласт элемент
(defun hvost (lst) 
(cond ((null (cdr lst)) (car lst))
	  (T (hvost (cdr lst)))))

; 12
(defun sum1 (lst n)
(sum1-inner lst n 0))
(defun sum1-inner (lst n res)
(cond ((or (null lst) (<= n 0)) res)
	  (T (sum1-inner (cdr lst) (- n 1) (+ res (car lst))))))

(defun sum2 (lst n)
(sum2-inner lst n 0 0))
(defun sum2-inner (lst n res tmp)
(cond ((null lst) res)
	  (T (sum2-inner (cdr lst) 
		             (- n 1) 
					 (cond ((> n 1) 0)
						   ((< (car lst) 0) res)
						   ((> (car lst) 0) (+ res (+ (car lst) tmp)))
						   (T (+ res (car lst))))
					 (cond ((> (car lst) 0) 0)
						   (T (+ tmp (car lst))))))))

(defun sum3 (lst n m d)
(sum3-inner lst n m (- d 1) 0 0))
(defun sum3-inner (lst n m d res tmp)
(cond ((or (null lst) (< m 0)) res)
	  (T (sum3-inner (cdr lst) 
					 (- n 1) 
					 (- m 1) 
					 d 
					 (cond ((and (<= n 0) (= tmp 0)) (+ res (car lst)))
						   (T res))
					 (cond ((or (= tmp d) (> n 0)) 0)
						   ((<= n 0) (+ 1 tmp))
						   (T 0))))))

; last-odd
(defun last-odd (lst)
(let ((x (last-odd-inner (cdr lst) (car lst)))) (and (oddp x) x)))
(defun last-odd-inner (lst od)
(cond ((null lst) od)
	  ((oddp (car lst)) (last-odd-inner (cdr lst) (car lst)))
	  (T (last-odd-inner (cdr lst) od))))

; 14
(defun cons-squad (lst)
(cond ((null lst) Nil)
	  (T (cons (* (car lst) (car lst)) (cons-squad (cdr lst))))))

; 15
(defun select-odd-rec (lst)
(cond ((null lst) nil)
	  ((oddp (car lst)) (cons (car lst) (select-odd-rec (cdr lst))))
	  (T (select-odd-rec (cdr lst)))))
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
 
(setf my_struct `((Nikita 1000 20 lisp-developer) (Dima 900 19 lisp-tester) (Andrey 666 21 lisp-hater)))
(defun sum-salary (lst) (sum-salary-inner lst 0))
(defun sum-salary-inner (lst res) 
(cond ((null lst) res)
	  (T (sum-salary-inner (cdr lst) (+ res (car (cdr (car lst))))))))
(defun change-salary (lst new n)
(reduce (lambda (res tmp)
(cond ((eq (my_len res) n) (append res (list (list (car tmp) new (cadr tmp)(caddr tmp)))))
	  (T (append res (list tmp)))))
lst :initial-value Nil))