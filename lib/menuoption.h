/**
 * @file
 * @date 2022-11-16 23:05:32 PM +0800
 */
#ifndef MENUOPTION_H
#define MENUOPTION_H

/**
 * MenuOption defines available options in the client menu
 */
typedef enum MenuOption
{
    PLANT_TREE = 1,
    QUERY_TREE,
    UPDATE_TREE,
    DISPLAY_ALL_TREES,
    EXIT_PROGRAM
} MenuOption;

/**
 * Handles menu option
 *
 * @param[in] sockfd Socket number of client
 * @param[in] semid Semaphore's id
 * @param[in] mo A MenuOption enum to be handle
 *
 * @return 0 if the handling succeeded, -1 if failed
 */
char *moption_handle(int new_sockfd, int semid, char *cli_addr, MenuOption mo);

/**
 * Display menu options
 *
 * @param[out] opt A MenuOption got from user's input
 *
 */
void moption_display(MenuOption *opt);

/**
 * Get menu option into readable string
 *
 * @param[in] op A menu option
 *
 * @return A string that specifies the name of menu option, NULL if the state is
 *         unknown
 */
const char *getMenuOptionName(enum MenuOption op);

#endif
