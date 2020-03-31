
(require 'company-irony-c-headers)
(add-hook 'c-mode-hook 'irony-mode)
(add-hook 'c++-mode-hook 'irony-mode)
(add-hook 'irony-mode-hook 'irony-cdb-autosetup-compile-options)
(eval-after-load 'company
  '(add-to-list 'company-backends '(company-irony-c-headers company-irony)))
(add-hook 'irony-mode-hook #'irony-eldoc)
;; (add-hook 'after-init-hook #'global-flycheck-mode)
;; (eval-after-load 'flycheck
;; 	'(add-hook 'flycheck-mode-hook #'flycheck-irony-setup))

(add-to-list 'auto-mode-alist '("\\.h\\'" . c++-mode))
(provide 'init-cpp)
