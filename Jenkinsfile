pipeline {
  agent { dockerfile true }
  stages {
    stage('build') {
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
    stage('test') {
      steps {
        sh '''
          cd build
          chmod +x tests
          bash tests
        '''
      }
    }

  }
}
