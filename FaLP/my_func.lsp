; Мой переворот списка.
(defun my_revers (lst) (my_rev lst Nil))

(defun my_rev (lst res) 
(cond ((null lst) res)
	  (T (my_rev (cdr lst) (cons (car lst) res)))))

	  
; Моя длина.
(defun my_len (lst)
(cond ((null lst) 0)
      (t (+ 1 (my_len(cdr lst))))))
	  
	  
; Мой последний элемент списка.
(defun my_last (lst) 
(cond ((null (cdr lst)) (car lst))
      (T (my_last (cdr lst))))) 


; Мой н-ный элемент списка.
(defun my_nth (lst n)
(cond ((null lst) Nil)
      ((= n 0) (car lst))
	  (T (my_nth (cdr lst) (- n 1)))))
	  
	  
; Мой минимальный элемент списка.
(defun my_min (lst)
(cond ((null lst) Nil)
      (T (my_m (cdr lst) (car lst)))))
	  
(defun my_m (lst m)
(cond ((null lst) m)
	  ((<(car lst) m) (my_m (cdr lst) (car lst)))
	  (T (my_m (cdr lst) m))))

	  
; Мое удаление. Аналогичное функции remove.
(defun my_rem (el lst) 
(cond ((null lst) Nil)
	  (T (reduce (lambda (res tmp)
				 (cond ((= el tmp) res)
					   (T (append res (list tmp)))))
lst :initial-value Nil))))


; Мое удаление версия 2. Удаляет первое вхождение.
(defun my_rem_v2 (el lst) 
(cond ((null lst) Nil)
	  (T (my_r el lst Nil))))
	  
(defun my_r (el lst res)
(cond ((null lst) res)
	  ((= el (car lst)) (append res (cdr lst)))
	  (T (my_r el (cdr lst) (append res (list (car lst)))))))
	  

; Моя сортировка. Находит минимум, удаляет минимум, вставляет минимум. Для удаления лучше юзать мое удаление версии 2. 
(defun my_sort (lst)
(cond ((null lst) Nil)
	  (T (my_s lst Nil))))

(defun my_s (lst res)
(cond ((null lst) res)
	  (T (my_s (remove (my_min lst) lst) (append res (list (my_min lst)))))))

(defun my_append (lst el)
(cond ((null lst) (cons el nil))
	  (T (cons (car lst) (my_append (cdr lst) el)))))
(defun my_append_list (lst1 lst2)
(cond ((null lst2) nil)
	  ((null lst1) (cons (car lst2) (my_append_list lst1 (cdr lst2))))
	  (T (cons (car lst1) (my_append_list (cdr lst1) lst2)))))