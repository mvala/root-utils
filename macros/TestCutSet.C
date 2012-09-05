void TestCutSet() {

  gSystem->Load("lib/libCutSet.so");

  TCutSet cs("MyCutSet","");
//  TCutObj c1("c1","");
  TCutObj c2("c2","");

  TCutSimple c1("c1","");
//  TCutSimple c2("c2","");

  TNamed *mySimpleObj = new TNamed("myObj","0");
//  TNamed *mySimpleObj = new TNamed("myObj","1");

//  cs.AddCut(&c1);
//  cs.AddCut(&c2);
  cs.AddCut(c1);
  cs.AddCut(c2);
  
  cs = c1&&c2;

  cs.Print();
  
//  TFormula *f = cs.GetFormula();
  Printf("Result : %d",(Bool_t)cs.IsSelected(mySimpleObj));
//  Printf("MyFormula1 : %d",(Bool_t)cs.IsSelected(new TObject()));

}
