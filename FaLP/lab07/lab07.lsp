(defun my_revers (lst) (my_rev lst Nil))

(defun my_rev (lst res) 
(cond ((null lst) res)
	  (T (my_rev (cdr lst) (cons (car lst) res)))))

; Полиндром
(defun pol (lst)
(compare lst (my_revers lst)))

(defun compare (lst1 lst2)
(cond ((null lst1) T)
      ((eq (car lst1) (car lst2)) (compare (cdr lst1) (cdr lst2)))))

; Сравнение множеств
(defun my_len (lst)
(cond ((null lst) 0)
      (t (+ 1 (my_len(cdr lst))))))
	  
(defun check_len (set1 set2)
(equal (my_len set1) (my_len set2)))

(defun find_set (el set2)
(cond ((null set2) Nil)
      ((eq el (car set2)) T)
      (T (find_set el (cdr set2)))))

(defun set-equal_rec (set1 set2)
(cond ((null set1) T)
      ((find_set (car set1) set2) (set-equal_rec (cdr set1) set2)))) 

(defun set-equal (set1 set2) 
(and (check_len set1 set2) (set-equal_rec set1 set2)))

; Таблица
(defun find_key (table key)
(cond ((null table) Nil)
      ((eq (caar table) key) (cdar table))
	  (T (find_key (cdr table) key))))

(defun find_value (table v)
(cond ((null table) Nil)
      ((eq (cdar table) v) (caar table))
	  (T (find_value (cdr table) v))))

(defun set_table () 
(setq table (list (cons `Russia `Moscow) 
				  (cons `Germany `Berlin) 
				  (cons `France `Paris))))

; swap-first-last
(defun my_last (lst) 
(cond ((null (cdr lst)) (car lst))
      (T (my_last (cdr lst))))) 
(defun first-to-last (lst)
(my_revers (cons (car lst)(cdr (my_revers (cdr lst))))))
(defun swap-first-last (lst)
(cons (my_last lst) (first-to-last lst)))

; swap-two-element
(defun my_nth (lst n)
(cond ((null lst) Nil)
      ((= n 0) (car lst))
	  (T (my_nth (cdr lst) (- n 1)))))
(defun swap-two-element (lst a b) 
(reduce (lambda (res tmp)
(cond ((eq (my_len res) a ) (append res (list (my_nth lst b))))
      ((eq (my_len res) b ) (append res (list (my_nth lst a))))
	  (T (append res (list tmp)))))
lst :initial-value Nil))

; swap-to-left
(defun swap-to-left (lst)
(append (cdr lst) (list (car lst))))

; swap-to-right
(defun swap-to-right (lst)
(append (list (my_last lst)) (my_revers (cdr (my_revers lst)))))