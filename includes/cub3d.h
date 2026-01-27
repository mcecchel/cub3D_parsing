/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:41:04 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 20:02:54 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <stdbool.h>

// =============================================
//           Strutture dati principali
// =============================================

// Struct per gestire immagini MLX per texture e schermo di rendering
typedef struct s_image
{
	void	*img;// Puntatore MLX all'immagine
	char	*addr;// Indirizzo memoria del pixel (per accesso diretto)
	int		bpp;// Bits x pixel (32?)
	int		line_len;// Byte per riga dell'immagine
	int		endian;// Ordine byte (little/big endian)
	int		width;// Larghezza in pixel
	int		height;// Altezza in pixel
}				t_image;

// Struct per salvare path e dati di ogni texture (nord, sud, est, ovest)
typedef struct s_texture
{
	char	*path;// Path del file immagine
	t_image	*img;// Img caricata con MLX
}				t_texture;

// Struct per salvare colori floor/ceiling in formato RGB e convertirli in hex per MLX
typedef struct s_color
{
	int		red;
	int		green;
	int		blue;
	int		hex;
}				t_color;

// Struct per gestire la posizione e direzione del player
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	char	spawn_dir;// Direzione iniziale spawn 'N','S','E','W'
	double	dir_x;// Dove guarda su asse x
	double	dir_y; // Dove guarda su asse y
	double	plane_x;// Angolo piano camera X
	double	plane_y;// Angolo piano camera Y
}				t_player;

// Struct per gestire la mappa di gioco
typedef struct s_map
{
	char	**grid;// Griglia 2D della mappa (array di stringhe)
	int		width;// Larghezza massima
	int		height;// Numero di righe
	int		player_count;// che deve essere 1
}				t_map;

// Struttura parsing. NB: da libere dopo il parsing
typedef struct s_parse
{
	char	**file_lines;
	int		line_count;// Per calcolare righe totali
	int		map_start;// Indice riga dove inizia la mappa
	bool	is_north_set;// Check se texture nord già settata
	bool	is_south_set;
	bool	is_west_set;
	bool	is_east_set;
	bool	is_floor_set;
	bool	is_ceiling_set;
}				t_parse;

/* // Struct per gestire raycasting
typedef struct s_ray
{
	double	camera_x;// Posiz su piano camera
	double	dir_x;// Direzione del raggio
	double	dir_y;
	int		map_x;// Cella corrente
	int		map_y;
	// DA AGGIUNGERE ROBA
}				t_ray; */

// Struttura principale
typedef struct s_game
{
	void		*mlx_init;
	void		*win;
	t_image		*screen;// Immagine schermo per rendering
	t_texture	*tex_north;// Texture parete nord
	t_texture	*tex_south;
	t_texture	*tex_west;
	t_texture	*tex_east;
	t_color		*floor;
	t_color		*ceiling;
	t_map		*map;
	t_player	*player;
	t_parse		*parse;
}				t_game;

// ==============================================
//               Validazione input
// ==============================================

// Controlla se il file ha estensione .cub
int		check_file_extension(char *filename);
// Controlla se il file esiste e se e' leggibile
int		check_file_access(char *filename);
// Funzione principale per validare l'input
int		validate_input(int ac, char **av);

// =============================================
//            Inizializzazione gioco
// =============================================

t_texture	*initialize_texture(void);
t_color		*initialize_color(void);
t_map		*initialize_map(void);
t_player	*initialize_player(void);
t_parse		*initialize_parse(void);
// Inizializzo la struttura di gioco
t_game		*init_structs(void);

// =============================================
//                 Lettura file
// =============================================

// Legge tutto il file e restituisce array di stringhe
char	**read_file_lines(char *filename, int *line_count);
// Carica il file nella struttura parse
int		load_file_to_parse(t_game *game, char *filename);
// Funzione principale lettura file (read_file.c)
char	**read_file(int fd);

// ==============================================
//              Utility per parsing
// ==============================================

// Controlla se una riga è vuota o se composta da solo spazi
int		is_line_empty(char *line);
// Salta spazi e tab, ritorna indice del primo char valido
int		skip_whitespaces(char *str, int index);
// Controlla se la riga inizia con un identificatore valido
int		is_valid_identifier(char *line);
int		is_valid_nbr(char *str);
// Utility aggiuntive (parse_utils.c)
char	*skip_whitespace(char *str);
int		count_commas(char *str);

// ==============================================
//            Identificazione elementi
// ==============================================

// Identifica dove inizia la mappa
int		find_map_start(t_game *game);
// Identifica tipo di elemento nella riga
int		identify_element(char *line);

// ==============================================
//                Parsing texture
// ==============================================

// Estrae il path della texture da una riga
char	*get_texture_path(char *line, int identifier_len);
// Verifica che il file texture esista
int		validate_texture_file(char *path);
int		parse_north_texture(t_game *game, char *line);
int		parse_south_texture(t_game *game, char *line);
int		parse_west_texture(t_game *game, char *line);
int		parse_east_texture(t_game *game, char *line);
// Funzione principale per parsing texture
int		parse_texture(t_game *game, char *line);
// Utility aggiuntive texture (parse_texture_utils.c)
char	*extract_texture_path(char *line);
int		validate_texture_path(char *path);

// ==============================================
//                 Parsing colori
// ==============================================

int		parse_floor_color(t_game *game, char *line);
int		parse_ceiling_color(t_game *game, char *line);
int		parse_color(t_game *game, char *line);

// Utility aggiuntive colori (parse_color_utils.c)

// Valida che un valore RGB sia nel range 0-255
int		validate_rgb_val(int value);
// Estrae e valida i 3 valori RGB da una stringa
int		parse_rgb_values(char *rgb_str, int *values);
// Converte valori RGB in formato hex
int		rgb_to_hex(int r, int g, int b);
// Estrae la stringa RGB da una riga
char	*extract_rgb_str(char *line, int identifier_len);

// ==============================================
//                Estrazione mappa
// ==============================================

// Riempie la griglia con le righe della mappa
int		fill_map_grid(t_game *game, char **map_grid, int map_width);
int		extract_map(t_game *game);

// Utility per parsing mappa (parse_map_utils.c)

// Calcola l'altezza della mappa (:quante righe NON vuote ci sono da map_start alla fine)
int		get_map_height(t_game *game);
// Calcola la larghezza massima della mappa (:trova la riga più lunga)
int		get_map_width(t_game *game);
// Se la riga è più corta di width, crea padding di spazi
char	*pad_map_line(char *line, int width);
// Alloca la griglia 2D per la mappa
char	**alloc_map_grid(int height);
// Libera le righe della mappa in caso di errore
void	free_map_rows(char **map_grid, int row_count);

// =============================================
//               Validazione mappa
// =============================================

// Valida caratteri e trova il player
int		validate_and_find_player(t_game *game);
// Verifica che la mappa sia chiusa
int		parse_map_borders(t_game *game);
// Validazione completa della mappa
int		parse_map(t_game *game);

// Utility

// Controlla se un carattere nella mappa è valido
bool	is_valid_map_char(char c);
// Controlla se il carattere è il player
bool	is_player_char(char c);
// Imposta la direzione del player convertendo il carattere (N/S/E/W) in vettori direzione e piano camera
void	set_player_direction(t_player *player, char dir);
// Inizializza posizione e direzione del player
void	init_player_position(t_game *game, int x, int y, char dir);

// ==============================================
//               Parsing principale
// ==============================================

int		parse_file(t_game *game, char *filename);

// ==============================================
//                  Gestione errori
// ==============================================

// Errori parsing file (parse_file_errors.c)
int		print_file_error(char *filename);
int		print_texture_error(int dir);
int		print_color_error(char type);
int		print_duplicate_error(char *element);
int		print_missing_element_error(void);

// ==============================================
//               Cleanup e Helpers
// ==============================================

// Libera array di stringhe (array 2D)
void	free_array(char **arr);
// Libera texture
void	free_texture(t_game *game, t_texture *texture);
// Libera mappa
void	free_map(t_map *map);
// Libera struttura di parsing
void	free_parse(t_parse *parse);
// Libera schermo
void	free_screen(t_game *game);
// Libera struttura di gioco completa
void	free_game(t_game *game);

#endif