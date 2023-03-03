" ---{ mappings }---
" allow gf to edit nonexistent files
    map gf :edit <cfile><CR>

" ex mode replaced with gq
    nnoremap Q gq

" 'replace all' aliased to S
    nnoremap S :%s//g<Left><Left>

" easily leave terminal buffer
    tnoremap <Leader><Esc> <C-\><C-n>

" delete visual selection with backspace
    xnoremap <BS> x

" perform dot commands over visual blocks
    xnoremap . :normal .<CR>

" rehighlight visual selection after indenting
    xnoremap < <gv
    xnoremap > >gv

" buffers
    map <Leader>bs :buffers<CR>:b
    map <Leader>bd :buffers<CR>:bd!
    map <Leader>bk :bd!<CR>
    map <Leader>bl :buffers<CR>
    map <Leader>bn :bn<CR>
    map <Leader>bp :bp<CR>

" compile and preview documents quickly
    map <Leader>c :w! \| !compiler "%:p"<CR>
    map <Leader>p :!opout "%:p"<CR><CR>

" easier tabs
    nnoremap <silent><tab> :if &modifiable && !&readonly && &modified <CR> :write<CR> :endif<CR>:bn<CR>
    nnoremap <silent><S-tab> :if &modifiable && !&readonly && &modified <CR> :write<CR> :endif<CR>:bp<CR>
    map <Leader><Tab> :tabnew<CR>
    noremap <Leader>1 1gt
    noremap <Leader>2 2gt
    noremap <Leader>3 3gt
    noremap <Leader>4 4gt
    noremap <Leader>5 5gt
    noremap <Leader>6 6gt
    noremap <Leader>7 7gt
    noremap <Leader>8 8gt
    noremap <Leader>9 9gt
    noremap <Leader>0 :tablast<CR>
    noremap <Leader>[ :tabprevious<CR>
    noremap <Leader>] :tabnext<CR>

" insert mode navigation
    inoremap <C-j> <Esc>A
    inoremap <C-k> <Esc>I

" move entire chunks in visual mode
    vnoremap J :m '>+1<CR>gv=gv
    vnoremap K :m '<-2<CR>gv=gv

" random shit
    nnoremap <C-d> <C-d>zz
    nnoremap <C-u> <C-u>zz

" window movements
    map <Leader>= <C-w>=
    map <Leader>- <C-w>s
    map <Leader>\ <C-w>v
    map <Leader>x <C-w>c
    map <C-h> <C-w>h
    map <C-j> <C-w>j
    map <C-k> <C-w>k
    map <C-l> <C-w>l
    map <C-Left> <C-w>h
    map <C-Down> <C-w>j
    map <C-Up> <C-w>k
    map <C-Right> <C-w>l

" spell checking
    map <Leader>o :setlocal spell! spelllang=en_us<CR>
    map <Leader>O ]sz=

" --{ plugin tweaks and hacks }--
" fzf customization
    let g:fzf_layout = { 'up': '~90%', 'window': { 'height': 0.8, 'width': 0.8, 'xoffset': 0.5, 'yoffset': 0.5 } }
    let $FZF_DEFAULT_OPTS = '--layout=reverse --info=inline'
    command! -bang -nargs=? -complete=dir Files
        \ call fzf#run(fzf#wrap('files', fzf#vim#with_preview({ 'dir': <q-args>, 'sink': 'e', 'source': 'rg --files --hidden' }), <bang>0))
    command! -bang -nargs=? -complete=dir AllFiles
        \ call fzf#run(fzf#wrap('allfiles', fzf#vim#with_preview({ 'dir': <q-args>, 'sink': 'e', 'source': 'rg --files --hidden --no-ignore' }), <bang>0))
    map <Leader>f :Files<CR>
    map <Leader>F :AllFiles<CR>

" NERDTree customization
    " nnoremap <expr> <Leader>n g:NERDTree.IsOpen() ? ':NERDTreeClose<CR>' : @% == '' ? ':NERDTree<CR>' : ':NERDTreeFind<CR>'
    " nmap <Leader>N :NERDTreeFind<CR>
    " autocmd BufEnter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif
    " if has('nvim')
    "     let NERDTreeBookmarksFile = stdpath('data') . '/NERDTreeBookmarks'
    " else
    "     let NERDTreeBookmarksFile = '$HOME/.config/nvim' . '/NERDTreeBookmarks'
    " endif
    " autocmd BufEnter * if bufname('#') =~ 'NERD_tree_\d\+' && bufname('%') !~ 'NERD_tree_\d\+' && winnr('$') > 1 |
    "     \ let buf=bufnr() | buffer# | execute "normal! \<C-W>w" | execute 'buffer'.buf | endif
    " let NERDTreeMinimalUI=1
    " let NERDTreeShowHidden=1

" vim-session settings
    let g:session_autosave='no'
    map <Leader>ss :SaveSession<Space>
    map <Leader>sS :SaveSession!<Space>
    map <Leader>so :OpenSession<Space>
    map <Leader>sO :OpenSession!<Space>
    map <Leader>sd :DeleteSession<Space>
    map <Leader>sD :DeleteSession!<Space>
    " set sessionoptions-=buffers

" vim-floaterm bindings
    let g:floaterm_keymap_new    = '<F9>'
    let g:floaterm_keymap_prev   = '<F10>'
    let g:floaterm_keymap_next   = '<F11>'
    let g:floaterm_keymap_toggle = '<F12>'

" remap default lf.vim binding
    let g:lf_map_keys = 0
    map <Leader>r :Lf<CR>
