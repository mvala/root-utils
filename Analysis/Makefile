
include Makefile.arch

PACKAGE = Analysis

$(PACKAGE): lib$(PACKAGE).so

EXTRAINC      = -I. $()

ifneq ($(ParallelTasks_INCLUDE),)
   EXTRAINC += -I../$(ParallelTasks_INCLUDE)
endif

ifeq ($(PLATFORM),macosx)
ROOTLIBDIR     := $(shell $(RC) --libdir)
endif

CHECKXML      := $(shell root-config --has-xml)

ifeq ($(CHECKXML),yes)
  CXXFLAGS += -DWITHXML
  CINTFLAGS += -DWITHXML
endif

CXXFLAGS += $(EXTRAINC) -g

SRCS = TAnalysisTask.cxx TAnalysisSelector.cxx TAnalysisManager.cxx TAnaInputHandler.cxx TAnaTaskExample.cxx
HDRS = TAnalysisTask.h TAnalysisSelector.h TAnalysisManager.h TAnaInputHandler.h TAnaTaskExample.h
DHDR = $(PACKAGE)LinkDef.h

DHDR_MY := $(DHDR)
HDRS_MY := $(HDRS)
SRCS_MY := $(SRCS) G__$(PACKAGE).cxx
OBJS_MY := $(SRCS_MY:.cxx=.o)

PARFILE       = $(PACKAGE).par


lib$(PACKAGE).so: $(OBJS_MY)
	@echo "Linking" $@ ...
	@/bin/rm -f $@
ifeq ($(PLATFORM),macosx)
	$(LD) $(SOFLAGS)$@ $(LDFLAGS) $^ $(OutPutOpt) $@ $(PACKLDFLAGS) $(EXPLLINKLIBS)
else
	$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(OutPutOpt) $@ $(PACKLDFLAGS) $(EXPLLINKLIBS)
endif
	@chmod a+x $@
	@echo "done"

%.o:    %.cxx %.h
	$(CXX) $(CXXFLAGS) $(PACKCXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS_MY) *.so G__$(PACKAGE).* $(PARFILE)

G__$(PACKAGE).cxx G__$(PACKAGE).h: $(HDRS) $(DHDR)
	@echo "Generating dictionary ..."
	rootcint -f $@ -c $(CINTFLAGS) $(EXTRAINC) $^

### CREATE PAR FILE

$(PARFILE): $(patsubst %,$(PACKAGE)/%,$(filter-out G__%, $(HDRS_MY) $(SRCS_MY) $(DHDR_MY) Makefile Makefile.arch PROOF-INF))
	@echo "Creating archive" $@ ...
	@tar cfzh $@ $(PACKAGE)
	@rm -rf $(PACKAGE)
	@echo "done"

$(PACKAGE)/Makefile: Makefile #.$(PACKAGE)
	@echo Copying $< to $@ with transformations
	@[ -d $(dir $@) ] || mkdir -p $(dir $@)
	@sed 's/include \$$(ROOTSYS)\/test\/Makefile.arch/include Makefile.arch/' < $^ > $@

$(PACKAGE)/Makefile.arch: $(ROOTSYS)/test/Makefile.arch
	@echo Copying $< to $@
	@[ -d $(dir $@) ] || mkdir -p $(dir $@)
	@cp -a $^ $@

$(PACKAGE)/PROOF-INF: PROOF-INF.$(PACKAGE)
	@echo Copying $< to $@
	@[ -d $(dir $@) ] || mkdir -p $(dir $@)
	@cp -a -r $^ $@

$(PACKAGE)/%: %
	@echo Copying $< to $@
	@[ -d $(dir $@) ] || mkdir -p $(dir $@)
	@cp -a $< $@

test-%.par: %.par
	@echo "INFO: The file $< is now tested, in case of an error check in par-tmp."
	@mkdir -p par-tmp
	@cd par-tmp; tar xfz ../$<;	cd $(subst .par,,$<); PROOF-INF/BUILD.sh
	@rm -rf par-tmp
	@echo "INFO: Testing succeeded (already cleaned up)"
