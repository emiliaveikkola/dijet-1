    {"count_c_d", count_c_d},
    {"count_c_antid", count_c_antid},
    {"count_c_u", count_c_u},
    {"count_c_antiu", count_c_antiu},
    {"count_c_s", count_c_s},
    {"count_c_antis", count_c_antis},
    {"count_c_c", count_c_c},
    {"count_c_antic", count_c_antic},
    {"count_c_b", count_c_b},
    {"count_c_antib", count_c_antib},
    {"count_c_g", count_c_g},

    {"count_antic_d", count_antic_d},
    {"count_antic_antid", count_antic_antid},
    {"count_antic_u", count_antic_u},
    {"count_antic_antiu", count_antic_antiu},
    {"count_antic_s", count_antic_s},
    {"count_antic_antis", count_antic_antis},
    {"count_antic_antic", count_antic_antic},
    {"count_antic_b", count_antic_b},
    {"count_antic_antib", count_antic_antib},
    {"count_antic_g", count_antic_g},

    {"count_s_d", count_s_d},
    {"count_s_antid", count_s_antid},
    {"count_s_u", count_s_u},
    {"count_s_antiu", count_s_antiu},
    {"count_s_s", count_s_s},
    {"count_s_antis", count_s_antis},
    {"count_s_b", count_s_b},
    {"count_s_antib", count_s_antib},
    {"count_s_g", count_s_g},

    {"count_antis_d", count_antis_d},
    {"count_antis_antid", count_antis_antid},
    {"count_antis_u", count_antis_u},
    {"count_antis_antiu", count_antis_antiu},
    {"count_antis_antis", count_antis_antis},
    {"count_antis_b", count_antis_b},
    {"count_antis_antib", count_antis_antib},
    {"count_antis_g", count_antis_g},

    {"count_antid_antid", count_antid_antid},
    {"count_antid_u", count_antid_u},
    {"count_antid_antiu", count_antid_antiu},
    {"count_antid_b", count_antid_b},
    {"count_antid_antib", count_antid_antib},
    {"count_antid_g", count_antid_g},

    {"count_d_d", count_d_d},
    {"count_d_antid", count_d_antid},
    {"count_d_u", count_d_u},
    {"count_d_antiu", count_d_antiu},
    {"count_d_b", count_d_b},
    {"count_d_antib", count_d_antib},
    {"count_d_g", count_d_g},

    {"count_antiu_antiu", count_antiu_antiu},
    {"count_antiu_b", count_antiu_b},
    {"count_antiu_antib", count_antiu_antib},
    {"count_antiu_g", count_antiu_g},

    {"count_u_u", count_u_u},
    {"count_u_antiu", count_u_antiu},
    {"count_u_b", count_u_b},
    {"count_u_antib", count_u_antib},
    {"count_u_g", count_u_g},

    {"count_antib_antib", count_antib_antib},
    {"count_antib_g", count_antib_g},

    {"count_b_b", count_b_b},
    {"count_b_antib", count_b_antib},
    {"count_b_g", count_b_g},
    
    {"count_g_g", count_g_g}


    ...............................................................count_g_g: 50419
count_u_g: 37654
count_antiu_g: 33161
count_c_g: 32732
count_antic_g: 32562
count_d_g: 28584
count_s_g: 27825
count_antis_g: 27788
count_antid_g: 26334
count_c_antic: 7641
count_antis_b: 6946











   int DetermineXJetType(int x, int y) {
    if (x == 3 && y == -4 || x == -3 && y == 4 ||
    x == 4 && y == -3 || x == -4 && y == 3) return 1;
    
    if (x == 3 && y == 4 || x == 4 && y == 3) return 2;

    if (x == -3 && y == -4 || x == -4 && y == -3) return 3;



    if (x == 3 && y == -1 || x == -3 && y == 1 ||
    x == 1 && y == -3 || x == -1 && y == 3) return 4;

    if (x == 3 && y == 1 || x == 1 && y == 3) return 5;

   if (x == -3 && y == -1 || x == -1 && y == -3) return 6;


      if (x == 4 && y == -1 || x == -4 && y == 1 ||
    x == 1 && y == -4 || x == -1 && y == 4) return 7;

    if (x == 4 && y == 1 || x == 1 && y == 4) return 8;

   if (x == -4 && y == -1 || x == -1 && y == -4) return 9;




   if (x == 3 && y == -2 || x == -3 && y == 2 ||
    x == 2 && y == -3 || x == -2 && y == 3) return 10;

   if (x == 3 && y == 2 || x == 2 && y == 3) return 11;

   if (x == -3 && y == -2 || x == -2 && y == -3) return 12;


   

   if (x == 4 && y == -2 || x == -4 && y == 2 ||
    x == 2 && y == -4 || x == -2 && y == 4) return 13;

   if (x == 4 && y == 2 || x == 2 && y == 4) return 14;

   if (x == -4 && y == -2 || x == -2 && y == -4) return 15;




   if (x == 3 && y == -5 || x == -3 && y == 5 ||
    x == 5 && y == -3 || x == -5 && y == 3) return 16;
   
   if (x == 3 && y == 5 || x == 5 && y == 3) return 17;

   if (x == -3 && y == -5 || x == -5 && y == -3) return 18;



   if (x == 5 && y == -4 || x == -5 && y == 4 ||
    x == 4 && y == -5 || x == -4 && y == 5) return 19;

   if (x == 5 && y == 4 || x == 4 && y == 5) return 20;

   if (x == -5 && y == -4 || x == -4 && y == -5) return 21;



   if (x == 3 && y == 21 || x == 21 && y == 3) return 22;

   if (x == -3 && y == 21 || x == 21 && y == -3) return 23;


   if (x == 4 && y == 21 || x == 21 && y == 4) return 24;

   if (x == -4 && y == 21 || x == 21 && y == -4) return 25;


   if (x == 1 && y == -2 || x == -1 && y == 2 ||
    x == 2 && y == -1 || x == -1 && y == 4) return 26;

   if (x == 1 && y == 2 || x == 2 && y == -1) return 27;

   if (x == -1 && y == -2 || x == -2 && y == -1) return 28;


   if (x == 2 && y == -5 || x == -2 && y == 5 ||
    x == 5 && y == -2 || x == -2 && y == 3) return 29;

   if (x == 2 && y == 5 || x == 5 && y == 2) return 30;

   if (x == -2 && y == -5 || x == -5 && y == -2) return 31;


   if (x == 5 && y == -1 || x == -5 && y == 1 ||
    x == 1 && y == -5 || x == -1 && y == 5) return 32;

   if (x == 5 && y == 1 || x == 1 && y == 5) return 33;

   if (x == -5 && y == -1 || x == -1 && y == -5) return 34;



   if (x == 2 && y == 21 || x == 21 && y == 2) return 35;

   if (x == -2 && y == 21 || x == 21 && y == -2) return 36;



   if (x == 1 && y == 21 || x == 21 && y == 1) return 37;

   if (x == -1 && y == 21 || x == 21 && y == -1) return 38;

   if (x == 21 && y == 21) return 50;

   return 100;
       }





       string vq2[] = {
    "ud", "x_ug", "x_dg", "x_uc", "x_ds", "x_db", "x_ud", "x_us", "x_dc", "x_ub",
    "x_antiud", "x_antiuantid", "x_antius", "x_antiuantis", "x_antids", "x_antidantis",
    "x_antiuc", "x_antiuantic", "x_antidc", "x_antidantic", "x_antiub", "x_antiuantib",
    "x_antidb", "x_antidantib", "x_antiug", "x_antidg"
};
int nq2 = sizeof(vq2) / sizeof(vq2[0]);



   

