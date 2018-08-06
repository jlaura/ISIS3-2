pipeline { 
    agent none
    environment {
        ISISROOT="${workspace}" + "/build/"
        ISIS3TESTDATA="/usgs/cpkgs/isis3/testData/"
        ISIS3DATA="/usgs/cpkgs/isis3/data/"
    }
    stages {
        stage('Fedora25') {
            agent {
                docker {
                    label 'cmake_cool'
                    image 'chrisryancombs/docker_isis'
                    args  '''\
                            -v /usgs/cpkgs/isis3/data:/usgs/cpkgs/isis3/data \
                            -v /usgs/cpkgs/isis3/testData:/usgs/cpkgs/isis3/testData\
                          '''  
                }
            }
            steps { 
                sh """
                    conda env create -n isis3 -f environment.yml
                    source activate isis3
                    mkdir -p ./install ./build && cd build
                    cmake -GNinja -DJP2KFLAG=OFF -DCMAKE_INSTALL_PREFIX=../install -Disis3Data=/usgs/cpkgs/isis3/data -Disis3TestData=/usgs/cpkgs/isis3/testData ../isis
                    set +e
                    cd build
                    ninja -j8 && ninja install
                    """
//                    export PATH="${PATH}:/opt/conda/envs/isis3/bin/:${workspace}/install/bin"
//                    export ISISROOT="${workspace}/install"
//                    ctest -j8 -R _unit_ --timeout 500
//                    ctest -j8 -R _app_ --timeout 500
//                   ctest -j8 -R _module_ --timeout 500
            }
        }
        stage('CentOS7') {
            agent {
                docker {
                    label 'cmake_cool'
                    image 'chrisryancombs/docker_isis_centos'
                    args  '''\
                            -v /usgs/cpkgs/isis3/data:/usgs/cpkgs/isis3/data \
                            -v /usgs/cpkgs/isis3/testData:/usgs/cpkgs/isis3/testData\
                          '''  
                }
            }
            steps {
                sh """
                    ls
                    pwd
                    conda env create -n isis3 -f environment.yml
                    source activate isis3
                    export PATH="${PATH}:/opt/conda/envs/isis3/bin/:${workspace}/install/bin"
                    export ISISROOT="${workspace}/install"
                    cd build
                    ctest -j8 -R _unit_ --timeout 500
                    ctest -j8 -R _app_ --timeout 500
                    ctest -j8 -R _module_ --timeout 500
                """
            }
        }
    }
//    post {
//        success {
//            sh 'pwd && ls'
//            archiveArtifacts artifacts: "build/objects/*.o"
//        }
//        always {
//            mail to: 'ccombs@usgs.gov',
//                    subject: "Build Finished: ${currentBuild.fullDisplayName}",
//                    body: "Link: ${env.BUILD_URL}"
//            sh "rm -rf build/* && rm -rf install/*"
//            cleanWs()
//        }
//    }
}
