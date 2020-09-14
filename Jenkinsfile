pipeline {
  agent { 
	dockerfile {
		args '-u root --privileged'	
    }
  }
  stages {
    stage('Build') {
      steps {
        sh '''
          cd data
          python save_data.py
          cd ..
          mkdir build && cd build
          cmake ..
          make
        '''
      }
    }
    stage('Test') {
      steps {
        sh '''
          cd build
          chmod +x tests
          ./tests --gtest_output=xml:results.xml
        '''
      }
    }
  }
  post {
        always {
            junit 'results.xml'
        }
    }
}
