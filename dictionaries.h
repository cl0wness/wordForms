#ifndef DICTIONARIES_H
#define DICTIONARIES_H
#include <QString>
#include <QStringList>

/// Словарь исключений множественного числа существительных
const QList <QStringList> exceptionNouns = {QStringList{ "man","men"},QStringList{ "woman","women"}, QStringList{ "foot","feet"},
                                       QStringList{ "tooth","teeth"}, QStringList{ "goose","geese"}, QStringList{ "mouse","mice"},
                                       QStringList{ "datum","data"}, QStringList{ "phenomenon","phenomena"}, QStringList{ "crisis","crises"},
                                       QStringList{ "basis","bases"}, QStringList{ "sheep","sheep"}, QStringList{ "deer","deer"},
                                       QStringList{ "crossroads","crossroads"}, QStringList{ "works","works"}, QStringList{ "means","means"},
                                       QStringList{ "species","species"}, QStringList{ "fish","fish"}, QStringList{ "child","children"},
                                       QStringList{ "person","people"}, QStringList{ "ox","oxen"}};

/// Словарь исключений степеней сравнения прилагательных
const QList <QStringList> exceptionAdjectives = {QStringList{ "good","better", "best"},QStringList{ "bad","worse", "worst"},
                                            QStringList{ "little","less", "least"}, QStringList{ "much/many","more", "most"},
                                            QStringList{ "far","farther/further", "farthest/furthest"}, QStringList{ "old","older/elder", "oldest/eldest"}};

/// Словарь исключений образования наречий
const QList <QStringList> exceptionAdverbs = {QStringList {"good", "well"} , QStringList{"fast", "fast"}, QStringList{"hard", "hard"},
                                         QStringList{"late", "late"}, QStringList {"low","low"}, QStringList{"easy", "easy/easily"}};

/// Словарь неправильных глаголов
const QList <QStringList> irregularVerbs = {QStringList{"abide","abode", "abode"}, QStringList{"arise","arose", "arisen"},
                                         QStringList{"awake","awoke", "awoken"},QStringList{"be","was/were", "been"},
                                         QStringList{"bear","bore", "borne/born"},QStringList{"beat","beat", "beaten"},
                                         QStringList{"become","became", "become"},QStringList{"beget","begat/begot", "begotten"},
                                         QStringList{"begin","began", "begun"},QStringList{"bend","bent", "bent"},
                                         QStringList{"bet", "bet", "bet"},QStringList{"bid", "bid/bade", "bid/bidden"},
                                         QStringList{"bite", "bit", "bitten"},QStringList{"bleed", "bled", "bled"},
                                         QStringList{"blow", "blew", "blown"},QStringList{"break", "broke", "broken"},
                                         QStringList{"bring", "brought", "brought"},QStringList{"broadcast", "broadcast", "broadcast"},
                                         QStringList{"build", "built", "built"},QStringList{"burn", "burnt/burned", "burnt/burned"},
                                         QStringList{"burst", "burst", "burst"},QStringList{"buy", "bought", "bought"},
                                         QStringList{"can", "could", "could"},QStringList{"cast", "cast", "cast"},
                                         QStringList{"catch", "caught", "caught"},QStringList{"chide", "chid/chode", "chid/chidden"},
                                         QStringList{"choose", "chose", "chosen"},QStringList{"cling", "clung", "clung"},
                                         QStringList{"clothe", "clad/clothed", "clad/clothed"},QStringList{"come", "came", "come"},
                                         QStringList{"cost", "cost", "cost"},QStringList{"creep", "crept", "crept"},
                                         QStringList{"cut", "cut", "cut"},QStringList{"deal", "dealt", "dealt"},
                                         QStringList{"dig", "dug", "dug"},QStringList{"dive", "dived", "dived/dove"},
                                         QStringList{"do", "did", "done"},QStringList{"draw", "drew", "drawn"},
                                         QStringList{"dream", "dreamt/dreamed", "dreamt/dreamed"},QStringList{"drink", "drank", "drunk"},
                                         QStringList{"drive", "drove", "driven"},QStringList{"dwell", "dwelt", "dwelt/dwelled"},
                                         QStringList{"eat", "ate", "eaten"},QStringList{"fall", "fell", "fallen"},
                                         QStringList{"feed", "fed", "fed"},QStringList{"feel", "felt", "felt"},
                                         QStringList{"fight" ,"fought", "fought"},QStringList{"find", "found", "found"},
                                         QStringList{"flee" ,"fled", "fled"},QStringList{"fling", "flung", "flung"},
                                         QStringList{"fly", "flew", "flown"},QStringList{"forbid", "forbade", "forbidden"},
                                         QStringList{"forecast", "forecast", "forecast"},QStringList{"foresee", "foresaw", "foreseen"},
                                         QStringList{"forget" ,"forgot", "forgotten/forgot"},QStringList{"forgive", "forgave", "forgiven"},
                                         QStringList{"forsake", "forsook", "forsaken"},QStringList{"freeze", "froze", "frozen"},
                                         QStringList{"get", "got", "gotten/got"},QStringList{"give", "gave", "given"},
                                         QStringList{"go", "went", "gone"},QStringList{"grind", "ground", "ground"},
                                         QStringList{"grow", "grew", "grown"},QStringList{"hang", "hung", "hung"},
                                         QStringList{"have", "had", "had"},QStringList{"hear", "heard", "heard"},
                                         QStringList{"hide", "hid", "hidden"},QStringList{"hit", "hit", "hit"},
                                         QStringList{"hold", "held", "held"},QStringList{"hurt", "hurt", "hurt"},
                                         QStringList{"keep", "kept", "kept"},QStringList{"kneel", "knelt/knelled", "knelt/kneeled"},
                                         QStringList{"know", "knew", "known"},QStringList{"lay", "laid", "laid"},
                                         QStringList{"lead", "led", "led"},QStringList{"lean" ,"leant/leaned", "leant/leaned"},
                                         QStringList{"leap" ,"leapt/leaped", "leapt/leaped"},QStringList{"learn", "learnt", "learnt"},
                                         QStringList{"leave", "left", "left"},QStringList{"lend", "lent", "lent"},
                                         QStringList{"let", "let", "let"},QStringList{"lie", "lay", "lain"},
                                         QStringList{"light", "lit/lighted", "lit/lighted"},QStringList{"lose", "lost", "lost"},
                                         QStringList{"make", "made", "made"},QStringList{"mean", "meant", "meant"},
                                         QStringList{"meet", "met", "met"},QStringList{"mow", "mowed", "mowed/mown"},
                                         QStringList{"offset", "offset", "offset"},QStringList{"overcome", "overcame", "overcome"},
                                         QStringList{"partake", "partook", "partaken"},QStringList{"pay", "paid", "paid"},
                                         QStringList{"plead", "pled/pleaded", "pled/pleaded"},QStringList{"preset", "preset", "preset"},
                                         QStringList{"prove" ,"proved", "proven/proved"},QStringList{"put", "put", "put"},
                                         QStringList{"quit", "quit", "quit"},QStringList{"read", "read", "read"},
                                         QStringList{"relay", "relaid", "relaid"},QStringList{"rend", "rent", "rent"},
                                         QStringList{"rid" ,"rid", "rid"},QStringList{"ring", "rang", "rung"},
                                         QStringList{"rise", "rose", "risen"},QStringList{"run", "ran", "run"},
                                         QStringList{"saw", "saw/sawed", "sawn/sawed"},QStringList{"say" ,"said", "said"},
                                         QStringList{"see", "saw", "seen"},QStringList{"seek" ,"sought", "sought"},
                                         QStringList{"sell", "sold", "sold"},QStringList{"send", "sent", "sent"},
                                         QStringList{"set", "set", "set"},QStringList{"shake", "shook", "shaken"},
                                         QStringList{"shed", "shed", "shed"},QStringList{"shine", "shone", "shone"},
                                         QStringList{"shoe", "shod", "shod"},QStringList{"shoot", "shot", "shot"},
                                         QStringList{"show", "showed", "shown"},QStringList{"shut", "shut", "shut"},
                                         QStringList{"sing", "sang", "sung"},QStringList{"sink" ,"sank/sunk", "sunk/sunken"},
                                         QStringList{"sit", "sat", "sat"},QStringList{"slay", "slew", "slain"},
                                         QStringList{"sleep" ,"slept", "slept"},QStringList{"slide", "slid", "slid"},
                                         QStringList{"slit", "slit", "slit"},QStringList{"smell", "smelt", "smelt"},
                                         QStringList{"sow", "sowed", "sown/sowed"},QStringList{"speak", "spoke", "spoken"},
                                         QStringList{"speed", "sped", "sped"},QStringList{"spell", "spelt", "spelt"},
                                         QStringList{"spend", "spent", "spent"},QStringList{"spill", "spilt/spilled", "spilt/spilled"},
                                         QStringList{"spin", "spun", "spun"},QStringList{"spit", "spat/spit", "spat/spit"},
                                         QStringList{"split", "split", "split"},QStringList{"spoil", "spoilt", "spoilt"},
                                         QStringList{"spread", "spread", "spread"},QStringList{"spring", "sprang", "sprung"},
                                         QStringList{"stand", "stood", "stood"},QStringList{"steal", "stole", "stolen"},
                                         QStringList{"stick" ,"stuck", "stuck"},QStringList{"sting","stung", "stung"},
                                         QStringList{"stink", "stank", "stunk"},QStringList{"strew", "strewed", "strewn/strewed"},
                                         QStringList{"strike", "struck", "stricken/struck"},QStringList{"strive", "strove", "striven"},
                                         QStringList{"swear", "swore", "sworn"},QStringList{"sweat", "sweat/sweated", "sweat/sweated"},
                                         QStringList{"sweep", "swept", "swept"},QStringList{"swell", "swelled/sweated", "swollen"},
                                         QStringList{"swim", "swam", "swum"},QStringList{"swing", "swung", "swung"},
                                         QStringList{"take", "took", "taken"},QStringList{"teach", "taught", "taught"},
                                         QStringList{"tear", "tore", "torn"},QStringList{"tell", "told", "told"},
                                         QStringList{"think", "thought", "thought"},QStringList{"thrive", "throve/thrived", "thriven/thrived"},
                                         QStringList{"throw", "threw", "thrown"},QStringList{"thrust", "thrust", "thrust"},
                                         QStringList{"typeset", "typeset", "typeset"},QStringList{"undergo", "underwent", "undergone"},
                                         QStringList{"understand", "understood", "understood"},QStringList{"wake", "woke", "woken"},
                                         QStringList{"wear", "wore", "worn"},QStringList{"weep", "wept", "wept"},
                                         QStringList{"wet", "wet/wetted", "wet/wetted"},QStringList{"win", "won", "won"},
                                         QStringList{"wind", "wound", "wound"},QStringList{"withdraw", "withdrew", "withdrawn"},
                                         QStringList{"wring", "wrung", "wrung"},QStringList{"write", "wrote", "written"}};

/// Словарь образования местоимений
const QList <QStringList> pronouns = {QStringList{"i","me","my","mine","myself"},QStringList{"you","you","your","yours","yourself/yourselves"},
                                   QStringList{"he","him","him","his","himself"},QStringList{"she","her","her","hers","herself"},
                                   QStringList{"it","it","its","its","itself"},QStringList{"we","us","our","ours","ourselves"},
                                   QStringList{"they","them","their","theirs","themselves"}};

/// Возможные формообразователи
const QList <QString> endings = {"s", "es", "ies",
                                 "r", "er", "ier",
                                 "st", "est", "iest",
                                 "ly", "ed", "ied", "ing"};
#endif // DICTIONARIES_H
