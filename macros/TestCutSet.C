void TestCutSet() {

   gSystem->Load("libCutSet.so");

   TCutSet cs("MyCutSet","");
   //  TCutObj c1("c1","");
   TCutObj c2("c2","");

   TCutSimple c1("c1","");
   //  TCutSimple c2("c2","");

   TNamed *mySimpleObj = new TNamed("myObj","0");
//   TNamed *mySimpleObj = new TNamed("myObj","1");

   //  cs.AddCut(&c1);
   //  cs.AddCut(&c2);
   cs.AddCut(c1);
   cs.AddCut(c2);

//   cs = c1&&c2;
//   cs = c1&&c2&&c1;
   cs = (c1&&c2)||(!c1&&!c2);

//   cs.Print();
   Printf("Result : %d",(Bool_t)cs.IsSelected(mySimpleObj));



   //  TFormula *f = cs.GetFormula();
//   TStopwatch timer;
//   timer.Start();
//   Bool_t ret = kTRUE;
//   for (Int_t i=0;i<1e7;i++){
//      cs.IsSelected(mySimpleObj);
//      ret = (1&1)||(!1&!1);
      //      ret = 1&1&0;
//   }
//   Printf("Result : %d",ret);
//   timer.Stop();
//   timer.Print();


   //  Printf("MyFormula1 : %d",(Bool_t)cs.IsSelected(new TObject()));

}
