(global-set-key (kbd "<F0>") 'open-init-file)
(with-eval-after-load 'company
  (define-key company-active-map (kbd "M-n") nil)
  (define-key company-active-map (kbd "M-p") nil)
  (define-key company-active-map (kbd "C-n") #'company-select-next)
  (define-key company-active-map (kbd "C-p") #'company-select-previous))

(normal-erase-is-backspace-mode t)


(provide 'init-keybindings)
