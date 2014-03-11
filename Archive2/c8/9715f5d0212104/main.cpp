int main()
{
    bool b = true;
    
    while( b )
    {
        int choice;
        
        //clrscr();
        printf("This is the main!\n");
        printf("\n\n\n\n[0] - Map");
        printf("\n[1] - Region Choice");
        //gotoxy(1,9);
        scanf("%d",&choice);
        switch(choice)
        {
            case 0:
                map();
                break;
            case 1:
                rc();
                break;
            default:
                printf("Invalid choice!");
        }
    }
    //getch();
    return 0;
}