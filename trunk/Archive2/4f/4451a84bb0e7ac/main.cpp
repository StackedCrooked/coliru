int
yyparse(void)
{
    struct
	{
		YYSTYPE	yyv;
		int	yys;
	} yys[YYMAXDEPTH], *yyp, *yypt;
	short *yyxi;
	int yyj, yym, yystate, yyn, yyg;
	YYSTYPE save1, save2;
	int save3, save4;
	long yychar;

	save1 = yylval;
	save2 = yyval;
	save3 = yynerrs;
	save4 = yyerrflag;

	yystate = 0;
	yychar = -1;
	yynerrs = 0;
	yyerrflag = 0;
	yyp = &yys[-1];
	goto yystack;

ret0:
	yyn = 0;
	goto ret;

ret1:
	yyn = 1;
	goto ret;

ret:
	yylval = save1;
	yyval = save2;
	yynerrs = save3;
	yyerrflag = save4;
	return yyn;

yystack:
	/* put a state and value onto the stack */
	if(yydebug >= 4)
		printf("char %s in %s", yytokname(yychar), yystatname(yystate));

	yyp++;
	if(yyp >= &yys[YYMAXDEPTH]) {
		yyerror("yacc stack overflow");
		goto ret1;
	}
	yyp->yys = yystate;
	yyp->yyv = yyval;

yynewstate:
	yyn = yypact[yystate];
	if(yyn <= YYFLAG)
		goto yydefault; /* simple state */
	if(yychar < 0)
		yychar = yylex1();
	yyn += yychar;
	if(yyn < 0 || yyn >= YYLAST)
		goto yydefault;
	yyn = yyact[yyn];
	if(yychk[yyn] == yychar) { /* valid shift */
		yychar = -1;
		yyval = yylval;
		yystate = yyn;
		if(yyerrflag > 0)
			yyerrflag--;
		goto yystack;
	}

yydefault:
	/* default state action */
	yyn = yydef[yystate];
	if(yyn == -2) {
		if(yychar < 0)
			yychar = yylex1();

		/* look through exception table */
		for(yyxi=yyexca;; yyxi+=2)
			if(yyxi[0] == -1 && yyxi[1] == yystate)
				break;
		for(yyxi += 2;; yyxi += 2) {
			yyn = yyxi[0];
			if(yyn < 0 || yyn == yychar)
				break;
		}
		yyn = yyxi[1];
		if(yyn < 0)
			goto ret0;
	}
	if(yyn == 0) {
		/* error ... attempt to resume parsing */
		switch(yyerrflag) {
		case 0:   /* brand new error */
			yyerror("syntax error");
			if(yydebug >= 1) {
				printf("%s", yystatname(yystate));
				printf("saw %s\n", yytokname(yychar));
			}
yyerrlab:
			yynerrs++;

		case 1:
		case 2: /* incompletely recovered error ... try again */
			yyerrflag = 3;

			/* find a state where "error" is a legal shift action */
			while(yyp >= yys) {
				yyn = yypact[yyp->yys] + YYERRCODE;
				if(yyn >= 0 && yyn < YYLAST) {
					yystate = yyact[yyn];  /* simulate a shift of "error" */
					if(yychk[yystate] == YYERRCODE)
						goto yystack;
				}

				/* the current yyp has no shift onn "error", pop stack */
				if(yydebug >= 2)
					printf("error recovery pops state %d, uncovers %d\n",
						yyp->yys, (yyp-1)->yys );
				yyp--;
			}
			/* there is no state on the stack with an error shift ... abort */
			goto ret1;

		case 3:  /* no shift yet; clobber input char */
			if(yydebug >= YYEOFCODE)
				printf("error recovery discards %s\n", yytokname(yychar));
			if(yychar == YYEOFCODE)
				goto ret1;
			yychar = -1;
			goto yynewstate;   /* try again in the same state */
		}
	}

	/* reduction by production yyn */
	if(yydebug >= 2)
		printf("reduce %d in:\n\t%s", yyn, yystatname(yystate));

	yypt = yyp;
	yyp -= yyr2[yyn];
	yyval = (yyp+1)->yyv;
	yym = yyn;

	/* consult goto table to find next state */
	yyn = yyr1[yyn];
	yyg = yypgo[yyn];
	yyj = yyg + yyp->yys + 1;

	if(yyj >= YYLAST || yychk[yystate=yyact[yyj]] != -yyn)
		yystate = yyact[yyg];
	switch(yym) {
		
case 5:
#line	48	"/sys/src/ape/cmd/make/gram.y"
 {
	    while( --nlefts >= 0)
		{
		wildp wp;

		leftp = lefts[nlefts];
		if(wp = iswild(leftp->namep))
			{
			leftp->septype = SOMEDEPS;
			if(lastwild)
				lastwild->next = wp;
			else
				firstwild = wp;
			lastwild = wp;
			}

		if(leftp->septype == 0)
			leftp->septype = sepc;
		else if(leftp->septype != sepc)
			{
			if(! wp)
				fprintf(stderr,
					"Inconsistent rules lines for `%s'\n",
					leftp->namep);
			}
		else if(sepc==ALLDEPS && leftp->namep[0]!='.' && yypt[-0].yyv.yshblock!=0)
			{
			for(lp=leftp->linep; lp->nxtlineblock; lp=lp->nxtlineblock)
			if(lp->shp)
				fprintf(stderr,
					"Multiple rules lines for `%s'\n",
					leftp->namep);
			}

		lp = ALLOC(lineblock);
		lp->nxtlineblock = NULL;
		lp->depp = yypt[-1].yyv.ydepblock;
		lp->shp = yypt[-0].yyv.yshblock;
		if(wp)
			wp->linep = lp;

		if(equal(leftp->namep, ".SUFFIXES") && yypt[-1].yyv.ydepblock==0)
			leftp->linep = 0;
		else if(leftp->linep == 0)
			leftp->linep = lp;
		else	{
			for(lpp = leftp->linep; lpp->nxtlineblock;
				lpp = lpp->nxtlineblock) ;
				if(sepc==ALLDEPS && leftp->namep[0]=='.')
					lpp->shp = 0;
			lpp->nxtlineblock = lp;
			}
		}
	} break;
case 7:
#line	105	"/sys/src/ape/cmd/make/gram.y"
 { lefts[0] = yypt[-0].yyv.ynameblock; nlefts = 1; } break;
case 8:
#line	106	"/sys/src/ape/cmd/make/gram.y"
 { lefts[nlefts++] = yypt[-0].yyv.ynameblock;
	    	if(nlefts>=NLEFTS) fatal("Too many lefts"); } break;
case 9:
#line	111	"/sys/src/ape/cmd/make/gram.y"
{
		char junk[100];
		sprintf(junk, "%s:%d", filestack[ninclude-1].fname, yylineno);
		fatal1("Must be a separator on rules line %s", junk);
		} break;
case 11:
#line	119	"/sys/src/ape/cmd/make/gram.y"
 { prevdep = 0;  yyval.ydepblock = 0; allnowait = NO; } break;
case 12:
#line	120	"/sys/src/ape/cmd/make/gram.y"
 { prevdep = 0; yyval.ydepblock = 0; allnowait = YES; } break;
case 13:
#line	121	"/sys/src/ape/cmd/make/gram.y"
 {
			  pp = ALLOC(depblock);
			  pp->nxtdepblock = NULL;
			  pp->depname = yypt[-0].yyv.ynameblock;
			  pp->nowait = allnowait;
			  if(prevdep == 0) yyval.ydepblock = pp;
			  else  prevdep->nxtdepblock = pp;
			  prevdep = pp;
			  } break;
case 14:
#line	130	"/sys/src/ape/cmd/make/gram.y"
 { if(prevdep) prevdep->nowait = YES; } break;
case 16:
#line	134	"/sys/src/ape/cmd/make/gram.y"
 { sepc = ALLDEPS; } break;
case 17:
#line	135	"/sys/src/ape/cmd/make/gram.y"
 { sepc = SOMEDEPS; } break;
case 18:
#line	138	"/sys/src/ape/cmd/make/gram.y"
 {yyval.yshblock = 0; } break;
case 19:
#line	139	"/sys/src/ape/cmd/make/gram.y"
 { yyval.yshblock = yypt[-0].yyv.yshblock; } break;
case 20:
#line	142	"/sys/src/ape/cmd/make/gram.y"
 { yyval.yshblock = yypt[-0].yyv.yshblock;  prevshp = yypt[-0].yyv.yshblock; } break;
case 21:
#line	143	"/sys/src/ape/cmd/make/gram.y"
 { yyval.yshblock = yypt[-1].yyv.yshblock;
			prevshp->nxtshblock = yypt[-0].yyv.yshblock;
			prevshp = yypt[-0].yyv.yshblock;
			} break;
	}
	goto yystack;  /* stack new state and value */
}
