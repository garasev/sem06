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