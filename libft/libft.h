/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:42:45 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/18 16:25:27 by narnaud@stude    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_slist
{
	void			*content;
	struct s_slist	*next;
}	t_slist;

typedef struct s_i_slist
{
	int					nb;
	struct s_i_slist	*next;
}	t_i_slist;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*previous;
}	t_dlist;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc( size_t num, size_t size );
int		ft_isalpha(int ch);
int		ft_isascii(int ch);
int		ft_isdigit(int ch);
int		ft_isprint(int ch);
int		ft_isalnum(int ch);
int		ft_isspace(int ch);
int		ft_isnumber(char *str);
void	*ft_memchr(const void *b, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	ft_free_split(char **split);

size_t	ft_ilen(int nbr);
size_t	ft_ulen(unsigned int nbr);
size_t	ft_longbaselen(long nbr, size_t base);
int		ft_croissant(int a, int b);
int		ft_decroissant(int a, int b);
int		ft_max(int a, int b);
int		ft_min(int a, int b);

void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
size_t	ft_strlen_to(const char *str, char ch);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
void	ft_strrev(char **str, unsigned int neg);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strjoin_with(char *s1, char *s2, char *inter);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *str, char ch);
char	*ft_itoa(int n);
char	*ft_itox(unsigned long n, const char *base);
char	*ft_utoa(unsigned int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_slist	*ft_slst_new(void *content);
void	ft_slst_add_front(t_slist **alst, t_slist *new);
int		ft_slst_size(t_slist *lst);
t_slist	*ft_slst_last(t_slist *lst);
void	ft_slst_add_back(t_slist **alst, t_slist *new);
void	ft_slst_delone(t_slist *lst, void (*del)(void *));
void	ft_slst_clear(t_slist **lst, void (*del)(void *));
void	ft_slst_iter(t_slist *lst, void (*f)(void *));
t_slist	*ft_slst_map(t_slist *lst, void *(*f)(void *), void (*del)(void *));

size_t	ft_ilst_first(t_i_slist *lst, int (*fct)(int a, int b));
void	ft_ilst_free(t_i_slist *list);
int		ft_ilst_is_in(int value, t_i_slist lst);

t_dlist	*ft_dlst_add(t_dlist *prev, void *content);
t_dlist	*ft_dlst_n(t_dlist *lst, size_t n);
char	**ft_dlst_to_arr(t_dlist	*ptr);
#endif
