; 3. Написать, по крайней мере, два варианта функции, 
; которая возвращает последний элемент своего списка-аргумента.
(defun my_last_1 (lst) (car (reverse lst)))
(defun my_last_2 (lst) (nth (- (length lst) 1) lst))
; 4. Написать, по крайней мере, два варианта функции, 
; которая возвращает свой список-аргумент без последнего элемента.
(defun non_cdr_1 (lst) (reverse (cdr (reverse lst))))
(defun non_cdr_2 (lst) (reverse (nthcdr 1 (reverse lst))))
; 5. Написать простой вариант игры в кости.
(defun roll () (+ 1 (random 6)))
(defun roll_dice (n) 
(let ((x (roll))
	  (y (roll)))
	 (and (print `(roll ,n)) (print x) (print y)
	      (cond ((and (eql x y) (or (eql x 1) (eql x 6))) (roll_dice n))
	            ((or (eql (+ x y) 7) (eql (+ x y) 11)) T)
		        (T (+ x y))))))
(defun play_1 ()
(let ((x (roll_dice 1))
	  (y (roll_dice 2)))
	 (cond ((eql x T) `(First player WIN))
	       ((eql y T) `(Second player WIN))
		   ((> x y) `(First player WIN))
		   ((eql x y) `(TIE))
		   (T `(Second player WIN)))))

(defun play_2 ()
(let ((x (roll_dice 1)))
	 (cond ((eql x T) `(First player WIN))
	       ((let ((y (roll_dice 2))) 
		   (cond ((eql y T) `(Second player WIN))
		         ((> x y) `(First player WIN))
		         ((eql x y) `(TIE))
		         (T `(Second player WIN))))))))