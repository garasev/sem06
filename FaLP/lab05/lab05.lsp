(defun first_even (x) (if (= 0 (mod x 2)) x (+ x 1)))
(defun abs_inc (x) (if (< x 0) (- x 1) (+ x 1)))
(defun sorted_pair (a b) (if (< a b) (list a b) (list b a)))
(defun middle_check (a b c) (if (or (and (< a b) (> a c)) (and (< a c) (> a b))) T Nil))
(defun first_check (a b) (if (> b a) Nil T))

(defun mid_if (a b c) (if (< a b) (if (> a c) T Nil) (if (> a b) (if (< a c) T Nil) Nil)))
(defun mid_cond (a b c) (cond ((< a b) (cond ((> a c) T))) ((> a b) (cond ((< a c) T)))))
(defun mid_and_or (a b c) (or (and (< a b) (> a c)) (and (> a b) (< a c))))

(defun how_alike (x y) 
(cond ((or (= x y) (equal x y)) `the_same)
	  ((and (oddp x) (oddp y)) `both_odd)
	  ((and (evenp x) (evenp y)) `both_even)
	  (T `difference)))

(defun how_alike_if (x y) 
(if (= x y) `the_same 
	(if (equal x y) `the_same 
		(if (oddp x) 
			(if (oddp y) `both_odd `difference) 
			(if (evenp x) 
				(if (evenp y) `both_even `difference) `difference))))) 

(defun how_alike_cond (x y) 
(cond ((= x y) `the_same)
	  ((equal x y) `the_same)
	  ((oddp x) (cond ((oddp y) `both_odd)
					  (T `difference)))
	  ((evenp x) (cond ((evenp y) `both_even)
					   (T `difference)))
	  (T `difference)))

(defun how_alike_and_or (x y)
(or (and (= x y) `the_same)
	(and (equal x y) `the_same)
	(and (oddp x) (oddp y) `both_odd)
	(and (evenp x) (evenp y) `both_even)
	(and `difference)))