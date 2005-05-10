%typemap(typecheck) QString = char *;
%typemap(typecheck) const QString & = char *;

%typemap(in) QString (char* tempptr) {
    if (gh_string_p($input)) {
        tempptr = SWIG_scm2str($input);
        $1 = QString(tempptr);
        if (tempptr) SWIG_free(tempptr);
    } else {
        SWIG_exception(SWIG_TypeError, "string expected");
    }
}

%typemap(in) const QString & (QString temp,
                             char* tempptr) {
    if (gh_string_p($input)) {
        tempptr = SWIG_scm2str($input);
        temp = QString(tempptr);
        if (tempptr) SWIG_free(tempptr);
        $1 = &temp;
    } else {
        SWIG_exception(SWIG_TypeError, "string expected");
    }
}

%typemap(out) QString {
    $result = gh_str02scm(($1).toAscii().constData());
}

%typemap(out) const QString & {
    $result = gh_str02scm(($1)->toAscii().constData());
}
