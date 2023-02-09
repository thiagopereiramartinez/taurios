/*
   ASCII Art
*/

/* estrutura da imagem */
typedef struct art_img {
   char name[40];
   struct {
      unsigned char x_img;
      unsigned char y_img;
      unsigned char c_img;
   } pix_img[2000];
} art_img;

/* mostrar arte */
void asciiart_display(art_img *ai);

